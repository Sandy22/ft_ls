# Ft_ls
[42 School](http://www.42.fr/) project !

Recoding one of the most used Unix command `ls` with some of its options.

## Description
Ft_ls opens the path to the Unix branch of 42.
The project show how to manage a sub-system of functions of operating system’s API, the associated data structures, as
well as the management of memory allocation and the associated data.

## Guidelines
Ft_ls behavior must be identical to the original `ls` command with the following variations:
* Amongst the numerous options available, I created the
following: `-l`, `-R`, `-a`, `-r` and `-t`.
* I didn't deal with the multiple column format for the exit when
the option `-l` isn’t in the arguments.
* I didn't deal with ACL and extended attributes.
* The overall display, depending on each option, must stay as identical as possible
to the system command, no information can be missing.

## Using it
```
usage: ls [-Ralrt] [file ...]
```
Ft_ls can be used exactly as the original command with the following options :

|Option|Action
|-|-|
|`-R`|   list subdirectories recursively
|`-a`|   do not hide entries starting with .
|`-l`|   use a long listing format
|`-r`|   reverse order while sorting
|`-t`|   sort by modification time

## More
* Subject from 42 : [-English](https://cdn.intra.42.fr/pdf/pdf/885/ft_ls.en.pdf) [-French](https://cdn.intra.42.fr/pdf/pdf/17/ft_ls.fr.pdf)

## Built With
* [SublimText](https://www.sublimetext.com/) - The text editor used

## Contributing
As always, if you see something that need to be added or changed, feel free to contribute !

## Author
[**Christophe Uzureau**](https://www.linkedin.com/in/christophe-uzureau-5b8168140)
