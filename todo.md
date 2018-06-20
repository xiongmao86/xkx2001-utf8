# Convert xkx2001 into utf8
* [x] convert config.xkx
* [x] convert u/
* [x] convert clone/
* [x] convert adm/
* [x] convert cmds/
* [x] convert d/
* [x] convert data/
* [x] convert doc/
* [x] convert include/
* [x] convert kungfu/
* [x] convert feature/
* [x] convert inherit/
* [x] convert help/

# Fix mudlib problems
* [ ] adm/daemons/securityd.c is broken. `create` function is incomplete.

# waiting list
* [ ] figure out the right edit, and finish adm/etc/welcome_newyear, the origin file is keeped as welcome_newyear.todo
* [ ] data/letter/x/xfaery.o saved as xfaery.todo

# Procedure **May contain mistakes.**
## none c or h files
### 1. Make sure no file name end with bak under the working folder
```shell
find . -name "*.bak"
```

### 2. Convert file other than *.c *.h goto step 6
```shell
find . -type f -not -name "*.c" -and -not -name "*.h" | sed /\.DS_Store/d | sed /^\.\\/log$/d | sed 's#\ #\\\\\ #g' | xargs -I {} sh -c "iconv -f gb18030 -t utf8 {} > {}.bak" 2>log
```

*Filter* .DS_Store ./log is filtered out with sed which is not needed with *.h and *.c version. If there are other file you don't want to process, add something like `sed /^\.\\/todo$/d` or `sed /^\.\\/log$/d` add it to the command.

Add `sed 's#\ #\\\\\ #g'` to escape space in file name.

### 3. Process log file
```shell
cat log| sed /^$/d | cut -d ":" -f 2 | sed s/^\ *//g | sed s/\ *$//g > lognext
mv lognext log
```
Remove empty line and cut path and trim line and > lognext. 

### 4. Find Binary files and remove their correspond .bak files from log
Sub algorithm:
1. Check there are any binary file in log. If there are none, goto next section.
```shell
file -f log
```
2. This should probable only done by hand? Replace sed pattern (`\ data$` for example) to delete binary file. And Go back to 1.
```shell
function filterout() {
    file -f log > lognext
    cat lognext | sed -n /$1/p | cut -d ":" -f 1 | sed 's#\ #\\\\\ #g' | xargs -I {} sh -c "rm {}.bak";
    cat lognext | sed /$1/d | cut -d ":" -f 1 > log
    rm lognext
}
```
Handy pick up.
```shell
filterout '[[:space:]]data$' # is \ text$
```

ps. The files in doc/help is really nasty so I use the quick way, open up with Sublime text 3 and use the plugin to filter out strange characters. After save and `convert xxx-subl`, usually it's good, and then handle the cleanup manually. quanzhen file is the really nasty one, toke me a long time to fix byte by byte, painful experience, so I just fail out using editors.

### 5. Process each file that are left in log 
```shell
function openup() {
    code $1.bak;
    open -a "Hex Fiend" $1
}
function convert() {
    iconv -f gb18030 -t utf8 $1 > $1.bak
    code $1.bak
}
function cleanup() {
    mv $1-gai.bak $1;
    rm $1-gai $1.bak
}
```
Algorithms process each file:
1. Open current converted file with vscode, and current working file with `Hex Fiend`(`openup xxx` or `openup xxx-gai` depending on whether this is your first time to process the file.) 
2. Find last two or there intelligible characters in vscode. 
3. Identify its hex code and bookmark them in Hex Fiend. This is the [recommended site.](http://mytju.com/classcode/tools/encode_gb2312.asp)
4. Find the nearest intelligilble character after the bookmark and bookmark them either.
5. Figure out what is added or what is lost between the bookmarks.
6. Edit and save to `xxx-gai`
7. Convert and show result with vscode `convert xxx-gai`.
9. If convert is not successful, goto 3.
10. If file is handling fine. `cleanup xxx`.
11. Process next file.

### 6. Move all `xxx.bak` files back to `xxx`, if processed is empty, goto 8.
```shell
find . -type f -not -name "*.c" -and -not -name "*.h" -and -not -name "*.bak" | sed /\.DS_Store/d | sed /^\.\\/log$/d | sed /^\.\\/processed/d | sed 's#\ #\\\\\ #g' | xargs -I {} sh -c "mv {}.bak {}" 2>processed
```

### 7. Process processed file
```shell
cat processed | cut -d ":" -f 2 | sed s/^\ *//g | sed s/\ *$//g | sed s/\.bak$//g > processednext
mv processednext processed
```

### 8. If every file in log are processed, we known nothing is neglected.
```shell
diff log processed
```
diff to see if log and processed is match. processed file make contain binary file that are excluded in log. Generate a list to `file -f list`, to see whether all of them are binary file.

After checking remove log and processed.
```shell
rm log processed
```

### 9. Git commit

## h files
### 10. Convert *.h files, if log is empty go to step 14.
```shell
find . -type f -name "*.h" | xargs -I {} sh -c "iconv -f gb18030 -t utf8 {} > {}.bak" 2>log
```
### 11. Process log file
```shell
cat log| sed /^$/d | cut -d ":" -f 2 | sed s/^\ *//g | sed s/\ *$//g > lognext
mv lognext log
```
### 12. Find Binary files and remove their correspond .bak files
Sub algorithm:
1. detect binary file
```shell
file -f log > lognext
```
2. This should probable only done by hand? Replace sed pattern (`\ data$` for example) to delete binary file.
Remember to update lognext each turn.
```shell
cat lognext | sed -n /\ data$/p | cut -d ":" -f 1 | xargs -I {} sh -c "rm {}.bak"
cat lognext | sed /\ data$/d > lognextnext
mv lognextnext lognext
```

3. After filter out every binary file, transform the filtered longnext back to log
```shell
cat lognext | cut -d ":" -f 1 > log
rm lognext
```

### 13. Process each file that are left in log 
```shell
function openup() {
    code $1.bak;
    open -a "Hex Fiend" $1
}
function convert() {
    iconv -f 18030 -t utf8 $1 > $1.bak
}
function cleanup() {
    mv $1-gai.bak $1;
    rm $1-gai $1.bak
}
```
Algorithms process each file:
1. Open current converted file with vscode, and current working file with `Hex Fiend`(`openup xxx.h` or `openup xxx.h-gai` depending on whether this is your first time to process the file.) 
2. Find last two or there intelligible characters in vscode. 
3. Identify its hex code and bookmark them in Hex Fiend. This is the [recommended site.](http://mytju.com/classcode/tools/encode_gb2312.asp)
4. Find the nearest intelligilble character after the bookmark and bookmark them either.
5. Figure out what is added or what is lost between the bookmarks.
6. Edit and save to `xxx.h-gai`
7. `convert xxx.h-gai`
8. check result by `code xxx.h-gai.bak` to see how is it going.
9. If convert is not successful, goto 3.
10. If file is handling fine. `cleanup xxx.h`.
11. Process next file.

### 14. Move all `xxx.h.bak` files back to `xxx.h`, if processed file is empty goto step 16
```shell
find . -type f -name "*.h" | xargs -I {} sh -c "mv {}.bak {}" 2>processed
```
### 15. Process processed file
```shell
cat processed | cut -d ":" -f 2 | sed s/^\ *//g | sed s/\ *$//g | sed s/\.bak$//g > processednext
mv processednext processed
```

### 16. If that every file in log are processed, we known nothing is neglected.
```shell
diff log processed
```
diff to see if log and processed is match. processed file make contain binary file that are excluded in log. Generate a list to `file -f list`, to see whether all of them are binary file.

After checking remove log and processed.
```shell
rm log processed
```
### 17. Git commit

## c files
The procedure is just like *.h files. Make a copy of section 'h files' and just replace ".h" with ".c".

### 17. Convert *.c files, if log is empty go to step 21.
```shell
find . -type f -name "*.c" | xargs -I {} sh -c "iconv -f gb18030 -t utf8 {} > {}.bak" 2>log
```
### 18. Process log file
```shell
cat log| sed /^$/d | cut -d ":" -f 2 | sed s/^\ *//g | sed s/\ *$//g > lognext
mv lognext log
```
### 19. Find Binary files and remove their correspond .bak files
Sub algorithm:
1. detect binary file
```shell
file -f log > lognext
```
2. This should probable only done by hand? Replace sed pattern (`\ data$` for example) to delete binary file.
Remember to update lognext each turn.
```shell
cat lognext | sed -n /\ data$/p | cut -d ":" -f 1 | xargs -I {} sh -c "rm {}.bak"
cat lognext | sed /\ data$/d > lognextnext
mv lognextnext lognext
```

3. After filter out every binary file, transform the filtered longnext back to log
```shell
cat lognext | cut -d ":" -f 1 > log
rm lognext
```

### 20. Process each file that are left in log 
```shell
function openup() {
    code $1.bak;
    open -a "Hex Fiend" $1
}
function convert() {
    iconv -f 18030 -t utf8 $1 > $1.bak
}
function cleanup() {
    mv $1-gai.bak $1;
    rm $1-gai $1.bak
}
```
Algorithms process each file:
1. Open current converted file with vscode, and current working file with `Hex Fiend`(`openup xxx.c` or `openup xxx.c-gai` depending on whether this is your first time to process the file.) 
2. Find last two or there intelligible characters in vscode. 
3. Identify its hex code and bookmark them in Hex Fiend. This is the [recommended site.](http://mytju.com/classcode/tools/encode_gb2312.asp)
4. Find the nearest intelligilble character after the bookmark and bookmark them either.
5. Figure out what is added or what is lost between the bookmarks.
6. Edit and save to `xxx.c-gai`
7. `convert xxx.c-gai`
8. check result by `code xxx.c-gai.bak` to see how is it going.
9. If convert is not successful, goto 3.
10. If file is handling fine. `cleanup xxx.c`.
11. Process next file.

### 21. Move all `xxx.c.bak` files back to `xxx.c`, if processed file is empty goto step 23
```shell
find . -type f -name "*.c" | xargs -I {} sh -c "mv {}.bak {}" 2>processed
```
### 22. Process processed file
```shell
cat processed | cut -d ":" -f 2 | sed s/^\ *//g | sed s/\ *$//g | sed s/\.bak$//g > processednext
mv processednext processed
```

### 23. If that every file in log are processed, we known nothing is neglected.
```shell
diff log processed
```
diff to see if log and processed is match. processed file make contain binary file that are excluded in log. Generate a list to `file -f list`, to see whether all of them are binary file.

After checking remove log and processed.
```shell
rm log processed
```
### 24. Git commit
