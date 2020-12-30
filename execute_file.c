#include "shell.h"

/**
 * execute_file - executes a file line by line
 * @fd: file descriptor
 * Return: exit status
 **/
int execute_file(int fd)
{
	char *prompt = get_prompt(fd);
	int status;

	while (shell.run)
	{
		signal(SIGINT, sigint_handler);
		printf("%s", prompt);
		args = get_tokens(fd);
		if (args == NULL)
			break;
		command = make_commands(args);
		status = fork_and_exec(command);
		free_command_chain(command);
	}
	
	return (status);
}
