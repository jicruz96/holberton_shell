#include "shell.h"


shell_t shell = {NULL, NULL, 0, 0};

/**
 * main - entry point to shell
 * @argc: arg count
 * @argv: argument array
 * @envp: environment variables array
 * Return: exit status
 **/
int main(int argc, char *argv[])
{
	int history_fd, history_size, status, fd = STDIN_FILENO;


	/* If an argument was passed, execute that and exit */
	if (argc > 1)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			sprintf(error_msg, "%s: %s", argv[0], argv[1]);
			perror(error_msg);
			return (errno);
		}
	}

	shell_init(argv[0], fd);

	if (shell.interactive)
	{
		history_fd = get_history(shell.history, &history_size);
		status = execute_hshrc();
	}

	status = execute_file(fd);
	if (shell.interactive)
		save_history_to_file(history_fd, history_size);
	return (status);
}

/**
 * shell_init - initializes new shell session
 * @shellname: shell name
 * @input: true if shell session is interactive, false if not
 **/
void shell_init(char *shellname, int input)
{
	shell.name = argv[0];
	shell.interactive = isatty(input);
	if (shell.interactive)
	{
		shell.history = malloc(sizeof(char *) * HISTSIZE);
		for (i = 0; i < HISTSIZE; i++)
			shell.history[i] = NULL;
	}

}
