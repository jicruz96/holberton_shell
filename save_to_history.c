#include "shell.h"

/**
 * save_line_to_history - saves a line to history array
 * @line: line to save in array
 **/
void save_line_to_history(char *line)
{
	static int end_index = HISTSIZE - 1;
	static int current_index;
	static size_t history_size = HISTSIZE;
	size_t i;

	if (current_index == 0)
		current_index = shell.history_size;

	if (current_index > end_index)
	{
		shell.history = realloc(shell.history, history_size + HISTSIZE);
		for (i = history_size; i < HISTSIZE + history_size; i++)
			shell.history[i] = NULL;
		history_size += HISTSIZE;
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
	int i;

	for (i = 0; shell.history[i]; i++)
	{
		if (i >= shell.history_size)
			write(shell.history_fd, shell.history[i], _strlen(shell.history[i]));
		free(shell.history[i]);
	}
	free(shell.history);
	close(shell.history_fd);
}
