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
	int fd = STDIN_FILENO;
	char *shellname = argv[0], error_msg[256];

	/* If an argument was passed, get its file descriptor */
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		/* if file does not exist, print error and exit */
		if (fd == -1)
		{
			sprintf(error_msg, "%s: 0: Can't open %s\n", argv[0], argv[1]);
			write(STDERR_FILENO, error_msg, _strlen(error_msg));
			return (CANT_OPEN);
		}
		shellname = argv[1];
	}

	/* Initialize shell */
	shell_init(shellname, fd);

	/* EXECUTION */
	if (shell.interactive)
		execute_hshrc();
	execute_file(fd);

	/* CLEAN UP */
	shell_cleanup();
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

	shell.run = true;
	shell.pid = getpid();
	shell.name = shellname;
	shell.lines = 1;
	shell.status = 0;
	shell.aliases = NULL;
	shell.interactive = isatty(input);
	environ = _realloc_string_array(environ, 0);
	if (shell.interactive)
	{
		shell.history = malloc(sizeof(char *) * HISTSIZE);
		for (i = 0; i < HISTSIZE; i++)
			shell.history[i] = NULL;
		shell.history_size = get_history(shell.history);
	}
}

/**
 * shell_cleanup - performs memory cleanups
 **/
void shell_cleanup(void)
{
	int i;
	alias_t *tmp;

	/* free line */
	_getline(-1);

	/* Save history to history file */
	if (shell.interactive)
		save_history_to_file();

	/* free environ array */
	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);

	/* free aliases */
	while (shell.aliases)
	{
		tmp = shell.aliases;
		shell.aliases = shell.aliases->next;
		free(tmp->alias), free(tmp->value), free(tmp);
	}
}

/**
 * execute_file - executes a file line by line
 * @fd: file descriptor
 * Return: exit status
 **/
void execute_file(int fd)
{
	char *prompt, **tokens = NULL;

	while (shell.run)
	{
		/* get and write shell prompt */
		prompt = get_prompt(fd);
		write(fd, prompt, _strlen(prompt));
		signal(SIGINT, sigint_handler);

		/* respond to user inputs */
		tokens = get_tokens(fd);
		if (tokens == NULL)
		{
			free(prompt);
			break;
		}

		/* execute line */
		execute_line(tokens);
		shell.lines++;
		free(tokens);

		/* cleanup */
		free(prompt);
	}
}

/**
 * execute_hshrc - executes the .hshrc file if it exists
 * Return: exit status of execute_file()
 **/
void execute_hshrc(void)
{
	int hshrc_fd;
	char *homedir, path[256], error_msg[256];

	/* create path for hshrc */
	homedir = _getenv("HOME");
	sprintf(path, "%s/%s", homedir, ".hshrc");
	free(homedir);

	/* go get .hshrc file descriptor */
	hshrc_fd = open(path, O_RDONLY);
	if (hshrc_fd == -1)
	{
		if (errno != ENOENT)
		{
			sprintf(error_msg, "%s: 0: Can't open %s\n", shell.name, path);
			write(STDERR_FILENO, error_msg, _strlen(error_msg));
		}
	}
	else
		execute_file(hshrc_fd);
}
