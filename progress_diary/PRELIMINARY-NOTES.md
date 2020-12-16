# Shell V2 Preliminary Notes


## Task 0 Notes:

* README - ✔
* man page - ❌
* AUTHORS.md - ❌
 
## Task 1 Notes:
 
* Pass Betty, simple.
 
## Task 2 notes
 
* Print file not found errors - ❌
* "Handle" (aka Print) errors period - ❌
* Handle EOF condition (exit program) - ❌
 
* Do `cd` - ❌
	* Remember that cd with no args == `cd $HOME` - ❌
    * Implement `cd -` --> change to previous directory - ❌
    * Update `PWD` variable whenever you change directory - ❌
 
* Do `exit` - ❌
	* "Must behave exactly like `sh`'s" - ❌
    * **No idea what this implies.. we'll have to do more research**
    * Handles arguments - ❌

* Do `env` (prints current environment) - ❌

Edge cases:
* Non-interactive mode. Must keep track of line numbers for error messages.

## Task 3 notes:

* Handle `>` (Usage: `command > output_file`) - ❌

Edge cases:
* `command >` and nothing else
* `>` and nothing else
* `> file`
* `command > directory`
* `> directory`
* `command > command`
* `file > command`
* `command > file_that_doesnt_exist`

## Task 4 notes:

[File Descriptors in bash](https://mywiki.wooledge.org/FileDescriptor)

Edge cases:
* Assigning a file descriptor to a new file
	* Ex: `exec 3> newfile`
* `command 10> file`
* `command n>`

## Task 5 notes:

* Handle `>>` (Usage `command >> output_file`)- ❌

Edge cases: same as Task 3 edge cases

## Task 6 notes:

* Handle `<` (Usage `command < input_file`) - ❌

Edge cases:
* `command1 < command2` - sh expects a file and will treat command2 as file name regardless
* same as Task 3 edge cases

## Task 7 notes:

* Handle `<<` (Usage `command << delimiter`) - ❌

Edge cases:
* `command << WORD other_thing` - should ignore heredoc entirely
* See Task 3 edge cases
* `command << WORD<br>WORD`

## Task 8 notes:

* Handle '|' pipes (Usage `command1 | command2`) - ❌

Edge cases:
* `command | file_or_directory`
* `command |`

## Task 9 notes:

* Handle the commands separator `;` - ❌

Edge cases:
* `;`
* `command;;`
* `command; command;;`

## Task 10 notes:

* Handle the `&&` logical operator - ❌

Edge cases:
* `command &&`
* `command &&& command`
* `command && >` or some other bizarre stuff like that


## Task 11 notes:

* Handle the `||` logical operator - ❌

Edge cases: see task 10

### Note:
In general, for tasks 3 through 11, before we build our architecture,
we must make sure we've fully understood and mapped out the order of
precedence for all the symbols. For example, if we are given:
```
echo "something" > txt; cat txt | cat && echo && echo && echo && cat < txt || [ 1 -e 1 ]
```
Our program needs to be built so that it can get the order of execution
exactly right. Therefore, **a flowchart detailing how we ought to parse
arguments given the established order of precedence is a must have**

See [this](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10_02)

## Task 12 notes:
* Implement the setenv and unsetenv builtin commands

__setenv__
- Initialize a new environment variable, or modify an existing one
- Command syntax: setenv VARIABLE VALUE
- Should print something on stderr on failure
___unsetenv___
- Remove a environment variable
- Command syntax: unsetenv VARIABLE
- Should print something on stderr on failure

Edge cases:

## Task 13 notes:

* Handle Ctrl+C: your shell should not quit when the user unputs ^C - ❌

Edge cases:

## Task 14 notes:

* Implement the `alias` builtin (Usage: `alias [name[='value' ...]`) - ❌
	* `alias`: Prints list of aliases with `name='value'` format
    * `alias name [name2 ...]`: Prints just these aliases
    * `alias name='value' [...]`: Defines an alias. If it exists, replaces it.
    
.{program_name}_aliases in $HOME directory


## Task 15 notes:

* handle variables replacement
* Handle $? variable
* Handle $$ variable

Reference: see [this](https://tldp.org/LDP/abs/html/internalvariables.html)

Note to selves: 
Those last two variables will probably require that we keep track of status
codes and previous commands. The history task will also require that. So we
should implement a "store previous commands" functionality from the outset.

## Task 16 notes:
* Handle comments (#)

## Task 17 notes
* Implement the `help` builtin command - ❌
* Usage: help [BUILTIN]


## Task 18 notes:

* Implement the `history` builtin command without any argument - ❌
	* Displays history list, one by line, preceded with line numbers, starting at 0 - ❌
    * On exit, write the entire history, without line numbers, to a file named .hsh_history in the directory $HOME - ❌
    * When the shell starts, read the file `.hsh_history` if it exists and set the first line number of the current session to the total number of lines in the file modulo `4096` - ❌

## Task 19 notes:

* Usage `hsh [filename]` - ❌

* The file contains all the commands that your shell should run before exiting
* "The file should contain one command per line" ... I don't get this. We're not in charge of the file. What the hell is this?
* No prompt!

## Task 20 notes:

* Handle a `.hshrc` file at startup - ❌
* `.hshrc` will be in the `$HOME` directory

## Task 21:

* Implement the `$PS1` prompt! - ❌
* Handle the following:
	* \d: date in "Day Month Date" format (e.g. "Wed Dec 15") - ❌
    * \H: hostname - ❌
    * \s: name of the shell - ❌
    * \u: username - ❌
    * \w: current working directory - ❌


## Allowed Functions & Syscalls

| Functions/Syscalls | Description | `Prototype |
|-|-|-|
| `access` | check real user's permissions for a file | `int access(const char *pathname, int mode);` |
| `chdir` | change working directory | `int chdir(const char *path);` |
| `close` | close a file descriptor | `int close(int fd);` |
| `execve` | executes the program pointed to by filename | `int execve(const char *filename, char *const argv[], char *const envp[]);` |
| `fork` | create a child process | `pid_t fork(void);` |
| `stat (__xstat)` | display file or file system status | `int stat(const char *path, struct stat *buf);` |
| `lstat (__lxstat)` | return information about a file | `int lstat(const char *path, struct stat *buf);` |
| `fstat (__fxstat)` | return information about a file | `int fstat(int fd, struct stat *buf);` |
| `kill` | send signal to a process | `int kill(pid_t pid, int sig);` |
| `open` | open and possibly create a file or device | `int open(const char *pathname. int flags);` |
| `read` | read from a file descriptor | `ssize_t read(int fd, void *buf, size_t count);` |
| `signal` | ANSI C signal handling | `typedef void (*sighandler_t)(int);`<br>`sighandler_t signal(int signum, sighandler_t handler);` |
| `wait` | wait for process to change state | `pid_t wait(int *status);` |
| `waitpid` | wait for process to change state | `pid_t waitpid(pid_t pid, int *status, int options);` |
| `wait3` | wait for process to change state, BSD style | `pid_t wait3(int *status, int options, struct rusage *rusage);` |
| `wait4` | wait for process to chagne state, BSD style| `pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);` |
| `write` | write to a file descriptor | `ssize_t write(int fd, const void *buf, size_t count);` |
| `exit` | terminate the calling process | `void _exit(int status);` |
| `dup` | duplicate a file descriptor | `int dup(int oldfd);` |
| `dup2` | duplicate a file descriptor | `int dup2(int oldfd, int newfd);` |
| `pipe` | create pipe | `int pipe(int pipefd[2]);`
| `unlink` | delete a name and possibly the file it refers to | `int unlink(const char *pathname);` |
| `time` | get time in seconds | `time_t time(time_t *t);` |
| `gethostname` | returns the null-terminated hostname in the character array name | `int gethostname(char *name, size_t len);` |
| `geteuid` | get user identity, returns the effective user ID of the calling process | `uid_t geteuit(void);` |
| `sigaction` | examine and change a signal action | `int sigaction(int sugnum, const struct sigaction *act, struct sigaction *oldact);` |
| `sigemptyset` | initializes the signal set given by set to empty, with all signals excluded from the set | `int segemptyset(sigset_t *set);` |
| `select` | synchronous I/O multiplexing, allow a program to monitor multiple file descriptors | `int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);` |
| `getpid` | get process identification | `pid_t getpid(void);` |
| `__errno_location (errno macros)` | man 2 errno |
| `closedir` | close a directory | `int closedir(DIR *dirp);` |
| `exit` | cause normal process termination | `void exit(int status);` |
| `free` | allocate and free dynamic memory | `void free(void *ptr);` |
| `getcwd` | get current working directory | `char *getcew(char *buf, size_t size);` |
| `getline` | delimited string input | `ssize_t getline(char **lineptr, size_t *n, FILE *stream);` |
| `malloc` | allocate and free dynamic memory | `void *malloc(size_t size);` |
| `opendir` | open a directory | `DIR *opendir(const char *name);` |
| `perror`| print a system error message | `void perror(const char *s);` |
| `readdir` | read a directory | `struct dirent *readdir(DIR *dirp);` |
| `strtok` | extract tokens from strings | `char *strtok(char *str, const char *delim);` |
| `localtime` | transform date and time to broken-down time or ASCII | `struct tm *localtime(const time_t *timep);` |
| `getpwuid` | get password file entry | `struct passwd *getpwuid(uid_t uid);` |
| `isatty` | test whether a file descriptor refers to a terminal | `int isaatty(int fd);` |
| `printf` | formatted output converstion | `int printf(const char *format, ...);` |
| `fflush` | flush a stream | `int fflush(FILE *stream);` |
| `fprintf` | formatted output conversion, write to the character string str | `int fprintf(FILE *stream, const char *format);` |
| `vfprintf` | formatted output converstion,  writes output to stdout | `int vprintf(const char *format, va_list ap);`
| `sprintf` | formatted output converstion, writes the character string str | `int sprintf(char *str, const char *format, ...);` |
