#include "shell.h"

/**
 * get_history - saves shell history to history array
 * @history: array where history will be saved
 * Return: history size
 **/
int get_history(char *history[])
{
	char path[256], *line = NULL, *homedir = _getenv("HOME");
	int i = 0, fd;

	sprintf(path, "%s/%s", homedir, ".hsh_history");
	free(homedir);

	fd = open(path, O_CREAT | O_RDONLY, 0644);

	for (i = 0; (line = _getline(fd)); i++)
	{
		if (i == HISTSIZE)
			while (i)
				free(history[i]), history[i--] = NULL;
		history[i] = line;
	}

	close(fd);
	return (i);
}
