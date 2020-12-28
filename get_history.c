#include "shell.h"

/**
 * get_history - saves shell history to history array
 * @history: array where history will be saved
 * Return: history file descriptor
 **/
int get_history(char *history[])
{
	char path[256];
	char *line = NULL;
	char *homedir = _getenv("HOME");
	size_t line_size = 0;
	int i = 0, fd;
	FILE *fp;

	sprintf(path, "%s/%s", homedir, ".hsh_history");
	fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("hsh");
		return (-1);
	}
	fp = fdopen(fd, "r+");
	while (getline(&line, &line_size, fp) != -1)
	{
		if (i == HISTSIZE)
			for (; i; i--)
				history[i] = NULL;
		history[i] = line;
		line = NULL;
		line_size = 0;
		i += 1;
	}
	return (fd);
}
