#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "strings/my_strings.h"

#define HISTSIZE		4096


#define DEFAULT_LOGIC	0000
#define IS_REDIR_OUT	0001
#define IS_REDIR_IN		0002
#define IS_APPEND		0004
#define IS_HEREDOC		0010
#define IS_AND          0020
#define IS_OR           0040
#define IS_PIPE         0100

#define EXIT_ERROR 		0777

#define IS_NUMERIC(x) ((x) >= '0' && (x) <= '9')

#define true			1
#define false			0
#define PS2				"> "

typedef int (*exec_f)(char *, char **);

/**
 * struct command_s - command struct
 * @logic:      macro that determines logic (see macros above)
 * @command:    command as a string
 * @path:       command path as a dynamically-allocated string
 * @args:       array of arguments for command (first argument must be command)
 * @input:      input name as string
 * @output:     output name as string
 * @heredoc:	heredoc string (if it exists)
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
	char *heredoc;
	exec_f executor;
	struct command_s *next;
	struct command_s *prev;
} command_t;

/**
 * struct shell_s - shell struct
 * @name: shell name
 * @history: shell history
 * @lines: lines read
 * @status: shell status
 **/
typedef struct shell_s
{
	char *name;
	char **history;
	int lines;
	int status;
	int interactive;
	int run;
} shell_t;


extern char **environ;
extern shell_t shell;

int execute_arg(char *argv[]);
int execute_hshrc(void);
char *_getenv(char *key);
char *get_prompt(int fd);
int get_history(char *history[], int *history_size);
int execute_file(int fd);
command_t *command_node_init(char *path);

int fork_and_exec(command_t *command);

int builtin_cd(char *path, char **args);
int builtin_setenv(char *path, char**args);
int builtin_alias(char *path, char **args);
int builtin_help(char *path, char **args);
int builtin_env(char *path, char **args);
int builtin_setenv(char *path, char **args);
int builtin_unsetenv(char *path, char **args);
int builtin_history(char *path, char **args);
int builtin_exit(char *path, char **args);
int execute_command(char *path, char **args);


exec_f get_executor(char *command);

void save_line_to_history(char *line, char **history, int line_no);
void save_history_to_file(char *history[], int history_fd, int line_no);
void sigint_handler(int signum);
void free_command_chain(command_t *head);
void handle_redir(command_t *, char **, int *);
void handle_and(command_t *, char **, int *);
void handle_pipe(command_t *, char **, int *);

char *get_program_path(char *program);
char *_getline(const int fd);
char *parse_line(char **string);
char **get_tokens(int fd);
command_t *make_commands(char **tokens);

int _strlen(char *str);
#endif /* SHELL_H */
