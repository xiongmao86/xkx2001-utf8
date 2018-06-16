# Convert xkx2001 into utf8
* [ ] convert config.xkx
* [x] convert u/
* [x] convert clone/
* [x] convert adm/
* [x] convert cmds/
* [ ] convert d/
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

### ?. Remove files whose name is binary file added with .bak
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
### ?+2. Process log file same as step 3
```shell
cat log| sed /^$/d | cut -d ":" -f 2 | sed s/^\ *//g | sed s/\ *$//g > lognext
mv lognext log
```
### ?+3. Find Binary files in log same as step 4
```shell
file -f log
```
### ?+4. Remove files whose name is binary file added with .bak
### ?+5. Process each file that are left in log
1. open current converted file(`code xxx.h.bak` or `code xxx.h-gai.bak` depending on whether this is your first time to process the file.)
2. to find last two or there intelligible characters.
3. find the exact hex code of those characters. this is the [recommended site.](http://mytju.com/classcode/tools/encode_gb2312.asp)
4. open current working file (`xxx.h` or `xxx.h-gai`) with Hex Fiend, find and bookmark that characters.
5. find out the nearest intelligilble character after the bookmark.
6. find out what is added or what is miss between the bookmarks.
8. edit and save to `xxx.h-gai`
9. `iconv -f gb18030 -t utf8 xxx.h-gai > xxx.h.gai.bak`
10. if convert is not successful, set current converted file as `xxx.h-gai.bak` refered to at 1 and current working file as `xxx.h-gai` refered at 4, goto 1.
11. check result by `code xxx.h-gai.bak` to see how is it going.
12. if there are still errors, goto 1 with converted file and working file set as  10 mentioned.
13. if file is handling fine. `mv xxx.h-gai.bak xxx.h`, `rm xxx.h-gai xxx.h.bak`.
14. process next file.
### ?+6 Move all `xxx.h.bak` files back to `xxx.h`
```shell
find . -type f -name "*.h" | xargs -I {} sh -c "mv {}.bak {}"
```
### ?+7 Remove log
```shell
rm log
```


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