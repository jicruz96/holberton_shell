#include "shell.h"

/**
 * execute_file - executes a file line by line
 * @fd: file descriptor
 * Return: exit status
 **/
void execute_file(int fd)
{
	char **tokens = NULL;
	char *prompt = isatty(fd) ? shell.prompt : "";
	command_t *commands = NULL;

	while (shell.run)
	{
		write(fd, prompt, _strlen(prompt));
		signal(SIGINT, sigint_handler);
		tokens = get_tokens(fd);
		if (tokens == NULL)
			break;
		commands = make_commands(tokens);
		fork_and_exec(commands);
		free_command_chain(commands);
		free(tokens);
	}

	if (isatty(fd))
		write(fd, "\n", 1);
}
