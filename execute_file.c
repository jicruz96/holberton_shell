#include "shell.h"

/**
 * execute_file - executes a file line by line
 * @fd: file descriptor
 * Return: exit status
 **/ 
int execute_file(int fd)
{
    int x = 0;
    
    /* if commmand->logic == IS_REDIRECT || IS_APPEND:
        /* command->output is the fd of command->output_name and we have to go get that
         * fd. If file doesn't exist, create it. Then, return that fd.
         *
        do_is_redirect_logic()
    else if command->logic == IS_PIPE:
        /* create pipe, set write end to our stdout and read end to command->next
         * command's stdin
         *
        do_pipe_logic()  

    /* if the input or the output aren't the usual 
    if command->input not stdin:
        stdin_copy = dup(stdin)
        dup2(command->input, stdin)
        /* dup some stuff */
        /*then dup2 some stuff 
    /* forking 
    fork()
    /* pipe closing if needed
    if child:
        if IS_PIPE:
            close(write_end_of_pipe)
            repipe()
        exec()
    
    if IS_PIPE:
        command->next = read_end_of_pipe
        
    /* execveing*/
    /* pipe closing */
    /* some waiting */
    /* if we piped, reset the pipes (dup2)
    dup2(stdin_copy, stdin)
    dup2(stdout_copy, stdin)
    `
} */
    return (0);
}