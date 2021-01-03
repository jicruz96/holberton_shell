#include "shell.h"

shell_t shell = {NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0};

/**
 * main - entry point to shell
 * @argc: arg count
 * @argv: argument array
 * Return: exit status
 **/
int main(int argc, char *argv[])
{
	int fd = STDIN_FILENO;
	char *error_msg = NULL;

	/* If an argument was passed, execute that and exit */
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			sprintf(error_msg, "%s: %s", argv[0], argv[1]);
			perror(error_msg);
			return (errno);
		}
	}

	/* fd is either STDIN or the argument file descriptor */
	shell_init(argv[0], fd);

	if (shell.interactive)
		execute_hshrc();

	execute_file(fd);
	_getline(-1);
	if (shell.interactive)
		save_history_to_file();
	return (shell.status);
}

/**
 * shell_init - initializes new shell session
 * @shellname: shell name
 * @input: true if shell session is interactive, false if not
 **/
void shell_init(char *shellname, int input)
{
	int i;

	shell.name = shellname;
	shell.prompt = get_prompt(input);
	shell.interactive = isatty(input);
	shell.status = 0;
	shell.pid = getpid();
	if (shell.interactive)
	{
		shell.history = malloc(sizeof(char *) * HISTSIZE);
		for (i = 0; i < HISTSIZE; i++)
			shell.history[i] = NULL;
		shell.history_size = get_history(shell.history);
	}
	shell.lines = 1;
	shell.run = true;
}
