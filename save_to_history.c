#include "shell.h"

/**
 * save_line_to_history - saves a line to history array
 * @line: line to save in array
 **/
void save_line_to_history(char *line)
{
	static int end_index = HISTSIZE - 1;
	static int current_index;
	static int history_size = HISTSIZE;
	int i;
	char **tmp;

	if (current_index == 0)
		current_index = shell.history_size;

	if (current_index > end_index)
	{
		history_size += HISTSIZE;
		tmp = malloc(sizeof(char) * (history_size));
		for (i = 0; i < history_size; i++)
			if (i >= end_index)
				tmp[i] = NULL;
			else
				tmp[i] = shell.history[i];
		free(shell.history);
		shell.history = tmp;
		end_index = history_size - 2;
	}
	shell.history[current_index] = line;
	current_index += 1;
}

/**
 * save_history_to_file - saves a line to history array
 **/
void save_history_to_file(void)
{
	int i, fd;
	char *home = _getenv("HOME");
	char history_path[256];

	sprintf(history_path, "%s/%s", home, ".hsh_history");
	fd = open(history_path, O_WRONLY | O_APPEND);
	free(home);
	for (i = 0; shell.history[i]; i++)
	{
		if (i >= shell.history_size)
			write(fd, shell.history[i], _strlen(shell.history[i]));
		free(shell.history[i]);
	}
	free(shell.history);
	close(fd);
}
