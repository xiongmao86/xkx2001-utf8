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
process log, rm empty line and find path and  trim pathstr and > lognext, this is needed for *.c *.h

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