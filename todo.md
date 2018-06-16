# Convert xkx2001 into utf8
* [ ] convert config.xkx
* [x] convert u/
* [x] convert clone/
* [x] convert adm/
* [x] convert cmds/
* [x] convert d/
* [ ] convert data/
* [ ] convert doc/
* [ ] convert feature/
* [ ] convert help/
* [ ] convert include/
* [ ] convert inherit/
* [ ] convert kungfu/

# waiting list
* [ ] complete the transformation of adm/etc/welcome_newyear, the origin file
is keeped as welcome_newyear.todo

# process **Draft Only**
## none c or h files
### 1. Make sure no file name end with bak under the working folder
```shell
find . -name "*.bak"
```
### 2. Convert file other than *.c *.h
```shell
find . -type f -not -name "*.c" -and -not -name "*.h" | sed /\.DS_Store/d | sed /^\.\\/log$/d |xargs -I {} sh -c "iconv -f gb18030 -t utf8 {} > {}.bak" 2>log
```

*Filter* .DS_Store ./log is filtered out with sed which is not needed with *.h and *.c version. If there are other file you don't want to process, add something like `sed /^\.\\/todo$/d` or `sed /^\.\\/log$/d` add it to the command.

**If log is empty, goto ?+1 Remove log file.**

### 3. Process log file
```shell
cat log| sed /^$/d | cut -d ":" -f 2 | sed s/^\ *//g | sed s/\ *$//g > lognext
mv lognext log
```
Remove empty line and cut path and trim line and > lognext.

### 4. Find binary files in log
```shell
file -f log
```

### ?. And remove those binary files' .bak file.
**If all files in log are binary files.**
```shell
find . -type f -name "*.bak" | xargs rm
```

### ?+1. Move converted files back to their origin name

### ?+2. Remove log file
```shell
rm log
```

### ?+3. Git commit

## h files
### ?+1. Convert *.h files
```shell
find . -type f -name "*.h" | xargs -I {} sh -c "iconv -f gb18030 -t utf8 {} > {}.bak" 2>log
```
### ?+2. Process log file
```shell
cat log| sed /^$/d | cut -d ":" -f 2 | sed s/^\ *//g | sed s/\ *$//g > lognext
mv lognext log
```
### ?+3. Find Binary files and remove their correspond .bak files
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

### ?+5. Process each file that are left in log **remember to paste back to #h file**
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
### ?+6 Move all `xxx.h.bak` files back to `xxx.h`
```shell
find . -type f -name "*.h" | xargs -I {} sh -c "mv {}.bak {}" 2>processed
```
### ?+7 Process processed file
```shell
cat processed | cut -d ":" -f 2 | sed s/^\ *//g | sed s/\ *$//g | sed s/\.bak$//g > processednext
mv processednext processed
```

### ?+7 If that every file in log are processed, we known nothing is neglected.
```shell
diff log processed
```
diff to see if log and processed is match. processed file make contain binary file that are excluded in log. Generate a list to `file -f list`, to see whether all of them are binary file.

After checking remove log and processed.
```shell
rm log processed
```
### ?+8 Git commit

## c files
The procedure is just like *.h files. Make a copy of section 'h files' and 
just replace ".h" with ".c".

### ?+1. Convert *.c files
```shell
find . -type f -name "*.c" | xargs -I {} sh -c "iconv -f gb18030 -t utf8 {} > {}.bak" 2>log
```
### ?+2. Process log file
```shell
cat log| sed /^$/d | cut -d ":" -f 2 | sed s/^\ *//g | sed s/\ *$//g > lognext
mv lognext log
```
### ?+3. Find Binary files and remove their correspond .bak files
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

### ?+5. Process each file that are left in log **remember to paste back to #h file**
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
### ?+6 Move all `xxx.h.bak` files back to `xxx.h`
```shell
find . -type f -name "*.c" | xargs -I {} sh -c "mv {}.bak {}" 2>processed
```
### ?+7 Process processed file
```shell
cat processed | cut -d ":" -f 2 | sed s/^\ *//g | sed s/\ *$//g | sed s/\.bak$//g > processednext
mv processednext processed
```

### ?+7 If that every file in log are processed, we known nothing is neglected.
```shell
diff log processed
```
diff to see if log and processed is match. processed file make contain binary file that are excluded in log. Generate a list to `file -f list`, to see whether all of them are binary file.

After checking remove log and processed.
```shell
rm log processed
```
### ?+8 Git commit

-------------------------------------
# How to process each folder **Draft Only**
**First** deal with all the files that are neither *.c file nor *.h file.

*Remember to take extra step 0* to make sure there are no ".bak" file, because
if there are, that would cause the rename step(which is step 4) to err. Read the
on option 1 in step 4 for detail command.
*Note*: There are better way to perform this task, I will update this when I 
figure out.

**Then** deal with all *.h files.

**Then** deal with all *.c files.

Once you finish one folder process next one.

# steps to take each turn **Draft Only**
## step 0: extra step when you are dealing none c or h file
check whether there are files end with *.bak
find . -name "*.bak"

## step 1
1. when process file other than *.c *.h
not *.c and not *.h, filter .DS_Store .tab ./todo ./log 
which is not needed with *.h and *.c version.

find . -type f -not -name "*.c" -and -not -name "*.h" | sed /\.DS_Store/d | sed /\.tab/d | sed /^\.\\/todo$/d | sed /^\.\\/log$/d |xargs -I {} sh -c "iconv -f gb18030 -t utf8 {} > {}.bak" 2>log

2. when process file that are *.h **unfinished!!!!**
*.h so don't need to filter things.
find . -type f -name "*.h" | xargs -I unfinished!

3. when process file that are *.c
*.c
find . -type f -name "*.c" | xargs -I {} sh -c "iconv -f gb18030 -t utf8 {} > {}.bak" 2>log

if log is empty finish.

## step 2
process log, rm empty line and cut path and trim line and > lognext, this is needed for *.c *.h

cat log| sed /^$/d | cut -d ":" -f 2 | sed s/^\ *//g | sed s/\ *$//g > lognext
rm log

## step 3
process files in lognext
exam file in hex mode
locate pitfall
fix
clean up temporary files make on the way

## step 4
1. when process files other than *.c and *.h **Cautious! the command is to be reexamed.**
**Cautious**: this command will rename everything name "{basename}.bak" into 
"{basename}" make sure you run step 0 to conform there are no file has the suffix
"bak", otherwise that would cause unexpected problem.

```shell
find . -type f -not -name "*.c" -and -not -name "*.h" | sed /\.DS_Store/d | sed /\.tab/d | sed /^\.\\/todo$/d | sed /^\.\\/log$/d |xargs -I {} sh -c "mv {}.bak {}"
```

3. when process files that are *.c
*.c
find . -type f -name "*.c" | xargs -I {} sh -c "mv {}.bak {}"