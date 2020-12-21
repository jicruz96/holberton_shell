#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DEFAULT         0000
#define IS_BUILTIN      0001
#define IS_HEREDOC      0002
#define IS_REDIR_OUT    0004
#define IS_REDIR_IN     0010
#define IS_APPEND       0020
#define IS_AND          0040
#define IS_OR           0100
#define IS_PIPE_WRITER  0200
#define IS_PIPE_READER  0400



typedef struct command_s
{
    int logic;
    char *command;
    int input; /* equal to stdin or a pipefd if a redirect */
    int output; /* equal to stdout or a pipefd if a ridirect */
    struct command_s *next;
    struct command_s *prev;
} command_t;



char *get_env(char *key);
char **tokenize(char *line);
int get_file_descriptor(char *filename);
int execute_file(int fd, char *prompt);
int execute(command_t *command);
command_t *make_commands(char *tokens);

/* PROMPT-MAKING FUNCTIONS */
char *get_prompt(void);

/**
* char *get_date(void);
* char *get_host(void);
* char *get_shellname(void);
* char *get_username(void);
* getcwd()
**/

#endif /* SHELL_H */