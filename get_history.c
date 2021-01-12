#include "shell.h"

/**
 * get_history - saves shell history to history array
 * @history: array where history will be saved
 * Return: history size
 **/
int get_history(char *history[])
{
	char path[256], *line = NULL, *homedir = _getenv("HOME");
	int i = 0, history_fd;

	/* create path to history file */
	sprintf(path, "%s/%s", homedir, ".hsh_history");
	free(homedir);

	history_fd = open(path, O_CREAT | O_RDONLY, 0644);

	/* copying history file contents to history struct */
	for (i = 0; (line = _getline(history_fd)); i++)
	{
		/* if 4096th command, then erase array and start as first command */
		if (i == HISTSIZE)
			while (i)
				free(history[i]), history[i--] = NULL;
		history[i] = line;
	}

	/* close history file */
	close(history_fd);
	return (i);
}
