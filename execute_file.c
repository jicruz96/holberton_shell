#include "shell.h"

/**
 * execute_file - executes a file line by line
 * @fd: file descriptor
 * Return: exit status
 **/
int execute_file(int fd)
{
	char *prompt = get_prompt(fd), **history = NULL;
	FILE *fp = fdopen(fd, 'r');
	exec_f executor = NULL;
	int line_no = 0;

	if (isatty(fd))
		history_fd = get_history(history);
	while (1)
	{
		printf("%s", prompt);
		signal(SIGINT, sigint_handler);
		if (get_tokens(fd) == NULL)
			goto CLEANUP;

		args = tokenize(line);
		command = make_commands(args);
		for (tmp = command; tmp; tmp = tmp->next)
		{
			executor = get_executor(command);
			tmp->line_no = line_no;
			if (_strcmp(tmp->command, "history") == 0)
				tmp->args = history;
			status = executor(tmp);
			if (isatty(fd))
				save_line_to_history(line, history);
			if (_strcmp(tmp->command, "exit") == 0)
				goto CLEANUP;
			line_no++;
		}
		free_command_chain(command);
	}

CLEANUP:
	if (isatty(fd))
		save_history_to_file(history, history_fd);
	return (status);
}
