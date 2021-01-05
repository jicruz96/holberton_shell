#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/types.h>
#include "strings/my_strings.h"

#define HISTSIZE 4096

#define DEFAULT_LOGIC 0000
#define IS_REDIR_OUT 0001
#define IS_REDIR_IN 0002
#define IS_APPEND 0004
#define IS_HEREDOC 0010
#define IS_AND 0020
#define IS_OR 0040
#define IS_PIPE 0100	
#define HAS_EXTRA 0200
#define BUILTIN_CD 0377
#define CD_FAIL 01000
#define NO_OLD_PWD 02000

#define EXIT_ERROR 0777

#define IS_NUMERIC(x) ((x) >= '0' && (x) <= '9')

#define true 1
#define false 0
#define PS2 "> "

typedef int (*exec_f)(char **);

/**
 * struct command_s - command struct
 * @logic:      macro that determines logic (see macros above)
 * @command:    command as a string
 * @path:       command path as a dynamically-allocated string
 * @args:       array of arguments for command (first argument must be command)
 * @input:      input name as string
 * @output:     output name as string
 * @extra_fd:	extra file descriptor (if 'n>' redirection, extra_fd = n)
 * @executor:	function that executes command
 * @next:       pointer to next command struct
 * @prev:       pointer to previous command struct
 **/
typedef struct command_s
{
	int logic;
	char *command;
	char *path;
	char **args;
	char *input;
	char *output;
	int extra_fd;
	exec_f executor;
	struct command_s *next;
	struct command_s *prev;
} command_t;

/**
 * struct shell_s - shell struct
 * @name: shell name
 * @prompt: shell prompt
 * @history: shell history
 * @run: if shell is running
 * @lines: lines read
 * @status: shell status
 * @history_fd: history file descriptor
 * @interactive: if shell is in interactive mode
 * @history_size: size of history
 **/
typedef struct shell_s
{
	char *name;
	char *prompt;
	char **history;
	int run;
	int lines;
	int status;
	int history_fd;
	int interactive;
	int history_size;
} shell_t;

extern char **environ;
extern shell_t shell;

void execute_hshrc(void);
char *_getenv(char *key);
char *get_prompt(int fd);
int get_history(char *history[]);
void execute_file(int fd);
command_t *command_node_init(char *path);

void fork_and_exec(command_t *cmd);
int execute_commands(command_t *command);
char **_realloc_string_array(char **array, int is_malloced);
int builtin_cd(char **args);
int builtin_setenv(char **args);
int builtin_alias(char **args);
int builtin_help(char **args);
int builtin_env(char **args);
int builtin_setenv(char **args);
int builtin_unsetenv(char **args);
int builtin_history(char **args);
int builtin_exit(char **args);
int execute_command(char **args);

exec_f get_executor(char *command);

int get_input_fd(command_t *cmd);
int get_output_fd(command_t *cmd);
void save_line_to_history(char *line);
void save_history_to_file(void);
void sigint_handler(int signum);
void free_command_chain(command_t *head);
void handle_redir(command_t *, char **, int *);
void handle_and(command_t *, char **, int *);
void handle_pipe(command_t *, char **, int *);
void shell_init(char *shellname, int input);
void print_stupid(char *str, int fd);

char *get_program_path(char *program);
char *_getline(const int fd);
char *parse_line(char **string);
char **get_tokens(int fd);
command_t *make_commands(char **tokens);

int clean_pipes(command_t *cmd, int *input_fd, int *output_fd);

char *fix_dquote(char **line, char *token, int fd);
char *get_heredoc(char **line, int fd);
char *_realloc(char *p, int size);

int handle_error(int code);
int _strlen(char *str);
#endif /* SHELL_H */
