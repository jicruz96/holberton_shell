# Shell V2

## **WARNING:** This project is currently in progress!
### Please come back on January 12, 2021 to see the final product!

---

## Overview

`shell` is a UNIX command interpreter. It is a replica of the `sh` shell, built from scratch in C. This project was developed as part of the Holberton School Low Level Systems specialization and is the second, more advanced version of the [simple shell project](https://github.com/jicruz96/JISH_A-Custom-Shell-Terminal) completed in the Foundations year.

This project was written by J.I. Cruz and Gabriel Abdul-Raheem.

## Installation 🛠

### Requirements
* Linux - gcc (>= 4.8.4)

Clone this repository to your local system. Use the following to compile the program and save the executable into a file named `shell`:
```
gcc -Wall -Werror -Wextra -pedantic *.c -o shell
```

## Usage 

* **Run the executable file (  `./shell`   ). Use the shell. *That's it!***
* Type `exit` or `Ctrl-D` to exit `shell`. 

### Non-interactive mode

You can also use `shell` non-interactively. Use `echo` to pipe in a command to `shell`. The program will execute the inputted command(s) without re-prompting.
```
$ echo "ls" | ./shell
```

## ✨ Features ✨

`shell` can run any executables in the PATH. The following built-in commands are also available:

| Built-in | Use |
|-|-|
| `exit [status]` |	Exit shell with specified exit status |
| `env`	| Print list of current environment variables |
| `setenv` | Set an environment variable |
| `unsetenv` | Unset an environment variable |
| `cd` | Change directories |
| `history` | Print command history |
| `help` | Display help for builtin commands |
| `alias [ALIAS='COMMAND']` | Alias a command as another. If no alias is given, print all aliases |

## Example Usage 🤷🏽‍♂️

* Coming Soon

## Release History 🧾

This is version 2.0 of a previous Holberton School project.

### Gabriel's Previous Shell
* [1.0 - First release - 17 Apr 2020](https://github.com/UsmanGTA/simple_shell) | *Written by Gabriel and [Usman Abdul-Jabbar](https://usmanjabbar.com)*

### J.I.'s Previous Shell
* [1.0 - First release - 17 Apr 2020](https://github.com/OctopusHugz/simple_shell/tree/5f9dbb9c0bc978b5f8566eac0ce5cc05496c22a0) | *Written by J.I. and [Colson Scott](https://github.com/OctopusHugz)*
* [1.1 - Second release - 15 Sep 2020](https://github.com/jicruz96/simple_shell) | *Because there was nothing better to do during COVID*

## Authors 👨🏽‍💻

* Gabriel Abdul Raheem [Github](https://github.com/GabrielAbdul) - [LinkedIn](https://www.linkedin.com/in/gabriel-abdul-raheem-3a1a01144/)
* J.I. Cruz [Github](https://github.com/jicruz96) - [LinkedIn](https://linkedin.com/in/jicruzpr)
