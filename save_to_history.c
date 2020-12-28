#include "shell.h"

/**
 * save_line_to_history - saves a line to history array
 * @line: line to save in array
 * @history: history array
 * @line_no: line number
 **/
void save_line_to_history(char *line, char *history[], int line_no)
{
	static int end_index = HISTSIZE - 1;
	static int current_index;
	static size_t history_size = HISTSIZE;

	if (current_index == 0)
		current_index = line_no;

	if (current_index > end_index)
	{
		history = realloc(history, history_size + HISTSIZE);
		memset(history + history_size, 0, HISTSIZE);
		history_size += HISTSIZE;
		end_index = history_size - 2;
	}
	history[current_index] = line;
	current_index += 1;
}

/**
 * save_history_to_file - saves a line to history array
 * @history: history array
 * @history_fd: file descriptor of history file
 * @line_no: where to start
 **/
void save_history_to_file(char *history[], int history_fd, int line_no)
{
	char **line = history + line_no;

	while (*line)
	{
		write(history_fd, *line, _strlen(*line));
		line += 1;
	}
	free(history);
	close(history_fd);
}
