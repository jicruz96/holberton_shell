#include "shell.h"

/**
 * execute_file - executes a file line by line
 * @fd: file descriptor
 * Return: exit status
 **/
void execute_file(int fd)
{
	char **tokens = NULL;
	char *prompt;

	while (shell.run)
	{
		prompt = get_prompt(fd);
		write(fd, prompt, _strlen(prompt));
		signal(SIGINT, sigint_handler);
		tokens = get_tokens(fd);
		if (tokens == NULL)
		{
			free(prompt);
			break;
		}
		execute_line(tokens);
		shell.lines++;
		free(tokens);
		free(prompt);
	}
}
