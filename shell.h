#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define IS_BUILTIN 01
#define IS_HEREDOC 02
#define IS_REDIR_OUT 04
#define IS_REDIR_IN 08
#define IS_APPEND 016
#define IS_AND 032
#define IS_OR 064
#define IS_PIPE_WRITER 0128
#define IS_PIPE_READER 0256

typedef struct command_s
{
    int logic;
    char *command;
    int input; /* equal to stdin or a pipefd if a redirect */
    int output; /* equal to stdout or a pipefd if a ridirect */
    struct command_s *next;
    struct command_s *prev;
} command_t;
char *get_prompt(void);
char *get_env(int argc, char **argv, char *envp[]);
char **tokenize(char *line);
int get_file_descriptor(char *filename);
int exeucte(command_t *command);
command_t *make_commands(char *tokens);
#endif /* SHELL_H */o