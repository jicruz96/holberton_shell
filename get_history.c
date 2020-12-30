#include "shell.h"

/**
 * get_history - saves shell history to history array
 * @history: array where history will be saved
 * Return: history file descriptor
 **/
int get_history(char *history[], int *history_size)
{
	char path[256], *line = NULL, *homedir = _getenv("HOME");
	int i = 0, fd;

	sprintf(path, "%s/%s", homedir, ".hsh_history");
	free(homedir);

	fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("hsh");
		return (-1);
	}
	
	for (i = 0; (line = _getline(fd)) != -1; i++)
	{
		if (i == HISTSIZE)
			while (i)
				free(history[i]), history[i--] = NULL;
		history[i] = line;
	}

	*history_size = i;
	if (isatty(STDIN_FILENO))
		shell.lines = i;
	
	return (fd);
}
