#include "shell.h"

/**
 * main - entry point to shell
 * @argc: arg count
 * @argv: argument array
 * @envp: environment variables array
 * Return: exit status
 **/
int main(int argc, char *argv[])
{
    char *prompt, *buf, *homedir;

    /* If an argument was passed, execute that and exit */
    execute_arg(argv);

    /* If no argument was passed, execute .hshrc */
    execute_hshrc();

    /* get prompt */
    prompt = get_prompt();
    exit_status = execute_file(STDIN_FILENO, prompt);
    post_work();
    return (exit_status);
}


    
    /* 
    /* checking for file as arg and .hshrc and doing the PS1 */

    /*********************** FLOW *********************/
    /*
    prompt = get_prompt()
    
	main_loop()	
		getline(input)
		tokenize(line)
		make_commands() -> returns command class with logic, name, input, output attributes
		for command in commands:
            pre_exec()
			execute(commands)
            save_command_to_history()
	post_work() /* saving the history, freeing_shit
	return (exit_status);*/
}