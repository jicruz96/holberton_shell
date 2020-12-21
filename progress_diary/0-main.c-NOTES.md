# 0 MAIN.c NOTES
Today we followed the basic flow of the shell, psuedocoding logic for what to do if our inputs had any pipes, operators, separators, or redirections. We made a list of mostly all the helper functions we need.

#include "shell.h"

/**
 * main - entry point to shell
 * @argc: arg count
 * @argv: argument array
 * @envp: environment variables array
 * Return: exit status
 **/
int main(int argc, char *argv[], char *envp[])
{
    /*
    char *prompt = "";
    int line_no = 0;
    fd = get_file_descriptor("$HOME/.hshrc");
    get_prompt() <-- "$ "; --> later, other logic
    loop_that(STDIN, prompt=prompt)
    pre_work() /* checking for file as arg and .hshrc and doing the PS1 */

    /*********************** FLOW *********************/
    homedir = get_env("HOME"); // get_env helper function 1
    sprintf(rc_path, "%s/%s", homedir, ".hshrc");
    fd = get_file_descriptor(rc_path); // get_file_descriptor helper function 2
    if fd != -1:
        loop_that(fd, prompt))
    fd = get_file_descriptor(argv[1]);
    if fd != -1:
        loop_that(fd, prompt)
        exit
    
    prompt = get_prompt()
    
	main_loop()	
		getline(input)
		tokenize(line)
		make_commands() -> returns command class with logic, name, input, output attributes
		for command in commands:
            pre_exec()
			execute(commands)
            save_command_to_history()
	post_work() /* saving the history, freeing_shit */
	return (exit_status);
}
post_work {
    save_history_file()
    free_everything()
}

/**
 * get_prompt - returns prompt
 * Returns: prompt
 **/
 char *get_prompt(void)
 {
    char *prompt = "$ "; 
    /**
    *  get_date()
    *  get_host()
    *  get_shellname()
    *  get_username()
    *  getcwd()
    **/
     
     return (prompt);
 } 
/**
 * get_env - finds and returns value of an environment variable
 * @key: environment variable
 * Return: value of environment variable 
 **/
char *get_env(int argc, char **argv, char *envp[])
{
    return (value);, 
}
/**
 * execute_file - executes a file line by line
 * @fd: file descriptor
 * Return: exit status
 **/ 
int execute_file(int fd)
{
    
    while ((line = getline()) != -1):
        args = tokenize(line);
        commands = make_commands(args)
        for command in commands:
            status = execute(command)
            save_history() // not helper, just reminder

}
/**
 * execute - wrapper for pipes vs non pipes 
 * @command: command node
 * Return: status
 */
int exeucte(command_t *command)
{
    int status;
    /** execute_pipe () **/
    
    
    return (status);
}    
/**
 * make_commands - makes linked list of commands and underlying logic from tokens
 * @tokens: tokens array
 * Return: head of command_t list
 */
command_t *make_commands(char *tokens)
{
    command_t *head;
    // make command
    return (head)
}
/**
 * tokenize - parses line input and returns token array, split by spaces
 *              and separators
 * @line: line to parse
 * Return: array of tokens
 **/
char **tokenize(char *line)
{
    char *tokens[];
    while (strtok(line))
    {
        // logic
    } 

    return (tokens)
}
/**
 * get_file_descriptor - returns file descriptor.
 *                      if file does not exist, creates file.
 *                      if file exists but wrong perms, returns -1
 * @filename: name of file
 * Return: file descriptor for file
 **/
int get_file_descriptor(char *filename)
{
    char *PATH = get_env("PATH");

    return (fd);
}
error_handler()
sig_handler()


execute {
    if commmand->logic == IS_REDIRECT || IS_APPEND:
        /* command->output is the fd of command->output_name and we have to go get that
         * fd. If file doesn't exist, create it. Then, return that fd.
         */
        do_is_redirect_logic()
    else if command->logic == IS_PIPE:
        /* create pipe, set write end to our stdout and read end to command->next
         * command's stdin
         */
        do_pipe_logic()  

    /* if the input or the output aren't the usual */
    if command->input not stdin:
        stdin_copy = dup(stdin)
        dup2(command->input, stdin)
        /* dup some stuff */
        /*then dup2 some stuff */
    /* forking */
    fork()
    /* pipe closing if needed */
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
    /* if we piped, reset the pipes (dup2) */
    dup2(stdin_copy, stdin)
    dup2(stdout_copy, stdin)
}

/* ls . > output && echo "done" */

#define IS_BUILTIN 01

#define IS_HEREDOC 02
#define IS_REDIR_OUT 04
#define IS_REDIR_IN 08
#define IS_APPEND 016
#define IS_AND 032
#define IS_OR 064

#define IS_PIPE_WRITER 0128
#define IS_PIPE_READER 0256

char **tokenize(char *line)
{
    char **args = malloc(MAX_ARGS);
    int i;

    allocate_to_null(args)
    i = 0
    tok = strtok(line, delim)
    while(tok)
        if tok.strip()[0] == '#':
            break
        args[i] = tok
        i += 1
        tok = strtok(NULL, delim)
    return args
}

cmmantd_t *make_commands(char **args) /* [ "echo", "-n", "something", "&&", "fakecommand",  "&&", "ls"] */
{
    int i;
    /* what needs to happen */
    prev_command = NULL
    for (i = 0; args[i]; i++)

        /* Getting command path */
        path = get_command_path(args[i]);
        if path == NULL:
            if path is built-in:
                command->logic = IS_BUILTIN;
            else:
                error()
        new_node = command_node_init(command, args[i])
        if prev:
            prev->next = new_node
        new_node->prev = prev
        i += 1
        if args[i] == NULL:
            break
       
        
        /* Getting it if it anything else: operators, redirects, pipes, separators, argument*/
        flag = True
        j = 0
        i = 0
        while args[i]:
            if args[i] is a redirect:
                command->logic = IS_REDIRECT
                if '<' then:
                    command->input_name = args[i + 1]
                else if '>':
                    command->output_name = args[i + 1]
                else if '>>':
                    command->output_name = args[i + 1]
                    command->logic = IS_APPEND
                i += 2
            else if args[i] is heredoc ('<<'):
                command->logic = IS_HEREDOC
                command->input = make_heredoc(args, &i)
                break
            else if args[i] is a pipe ('||'):
                command->logic = IS_PIPE_WRITER
                i += 1
                break
            else if args[i] is a operators ('&&', '||'):
                command->logic = either AND or OR depending on whats args[i] is
            else:
                command->args[j] = args[i]
                j += 1
                i += 1

        prev_command = new_node

    return head
}

command_t *command_node_init(char *path, char *command)
{
    command_t *new = malloc(sizeof(command_t));

    if (!new)
        return (NULL);
    new->path = path;
    new->command = command;
    new->input = STDIN_FILENO;
    new->output = STDOUT_FILENO;
    new->args = NULL;
    new->next = new->prev = NULL;
    return new;

}
char *get_program_path(char *arg)
{
    loop_through_folder in PATH and check if file exists in that folder in the path
    if it does, if we have permission to open it
        return concat(path,'/',arg)
    if it doesnt, check if the string itself is a valid file path. if it is:
        return arg
    else:
        return NULL
}
typedef struct command_s
{
    int logic; /* IS_REDIRECT, IS_PIPE  0 IS_HEREDOC */
    char *command;
    char *input; /* equal to stdin or a pipefd if a redirect */
    int output; /* equal to stdout or a pipefd if a ridirect */
    char **args;
    struct command_s *next;
    struct command_s *prev;
} command_t;

main_loop {

    while (getline() != -1)
    {
        
    }
    
}

tokenize {
    /** inputs
     *  - line
     **/
     /** output:
      * - array of arguments split by spaces
      **/
      /* what needs to happen ? */
}

void pre_work(void)
{
    /* history */
    /* what are our inputs ? */
    /**
     *  - .hsh_history
     *  - $HOME
    /* what is being output ? */
    /* line number = len(.hsh_history) % 4096 or len(.hsh_history) if < 4096*/

    /* what needs to happen ? */
    

    /* .hshrc */
    /** inputs:
     * - $HOME
     * - .hshrc
     **/
     /** outputs:
      * a file descriptor to hshrc -> pass to getline loop but don't exit
      **/

    /* what needs to happen ?
    THIS HAPPENS IN THE LOOP THAT FUNCTION
        char *history[1000];
        fd = get_file_descriptor("$HOME/.hsh_history");
        if fd != -1:
            line_no = get_line_numbers(fd)
        else:
            create(".hsh_history")*/
    /* get_file_descriptor(); */

    /* filename as argument */
    /** inputs
     * - if exists, argv[1], else don't bother
     */
     /** outputs
      * file descriptor to that file...
      */
      /* get_file_descriptor(); */

    /* prompt */
    /** inputs
     * the PS1 environment variable
     **/
     /** output
      * char *prompt = "$ ";
      **/
      /* what needs to happen */
      /* get_prompt() */

}           