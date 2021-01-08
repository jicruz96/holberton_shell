#include "shell.h"

shell_t shell = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/**
 * main - entry point to shell
 * @argc: arg count
 * @argv: argument array
 * Return: exit status
 **/
int main(int argc, char *argv[])
{
	alias_t *tmp;
	int fd = STDIN_FILENO, i;

	/* If an argument was passed, execute that and exit */
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			dprintf(STDERR_FILENO, "%s: 0: Can't open %s\n", argv[0], argv[1]);
			return (errno);
		}
		shell_init(argv[1], fd);
	}
	else
	{
		shell_init(argv[0], fd);
	}

	if (shell.interactive)
		execute_hshrc();

	execute_file(fd);
	_getline(-1);
	if (shell.interactive)
		save_history_to_file();
	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
	while (shell.aliases)
	{
		tmp = shell.aliases;
		shell.aliases = shell.aliases->next;
		free(tmp->alias), free(tmp->value), free(tmp);
	}
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
	shell.aliases = NULL;
	environ = _realloc_string_array(environ, 0);
}
