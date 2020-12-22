#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define DEFAULT_LOGIC   0000

#define REDIR_OUT       0001
#define REDIR_IN        0002
#define APPEND          0004
#define HEREDOC         0010
#define REDIR           (IS_REDIR_OUT | IS_REDIR_IN | IS_APPEND | IS_HEREDOC)
#define IS_REDIR(x)     ((x) & (REDIR))

#define AND_OP          0020
#define OR_OP           0040
#define IS_AND(x)       ((x) & (AND_OP))
#define IS_OR(x)        ((x) & (OR_OP))

#define PIPE_WRITER     0100
#define PIPE_READER     0200
#define PIPE            (IS_PIPE_WRITER | IS_PIPE_READER)
#define IS_PIPE(x)      ((x) & (PIPE))

/**
 * struct command_s - command struct
 * @logic:      macro that determines logic (see macros above)
 * @command:    command as a string
 * @path:       command path as a dynamically-allocated string
 * @args:       array of arguments for command (first argument must be command)
 * @input:      input name as string
 * @input_fd:   input file descriptor
 * @output:     output name as string
 * @output_fd:  output file descriptor
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
    int input_fd;
    char *output
    int output_fd;
    struct command_s *next;
    struct command_s *prev;
} command_t;

typedef int (*exec_f)(command_t *);

int execute_arg(char *argv[]);
int execute_hshrc(void);
char *get_env(char *key);
char *get_prompt(int fd);
int execute_file(int fd);
command_t *command_node_init(char *path, char *command);


int fork_and_exec(command_t *command);
int builtin_cd(command_t *command);
int builtin_setenv(command_t *command);
int builtin_unsetenv(command_t *command);
int builtin_env(command_t *command);
int builtin_alias(command_t *command);
int builtin_history(command_t *command);
int clean_and_exit(command_t *command);

exec_f get_executor(command_t *command);

void save_to_history(char *line, char **history);

void free_command_chain(command_t *head);


char *get_program_path(char *program);

command_t *make_commands(char *tokens);

char **tokenize(char *line);

/* PROMPT-MAKING FUNCTIONS */

/**
* char *get_date(void);
* char *get_host(void);
* char *get_shellname(void);
* char *get_username(void);
* getcwd()
**/

#endif /* SHELL_H */
