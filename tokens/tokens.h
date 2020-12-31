#ifndef TOKENS_H
#define TOKENS_H
#include "../shell.h"

void handle_redir(command_t *, char *, int *);
void handle_and(command_t *, char *, int *);
void handle_pipe(command_t *, char *, int *);

#endif /* TOKENS_H */