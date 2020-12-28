#include "shell.h"

/**
 * main - test file for history helpers
 * Return: 0
 **/
int main(void)
{
	char **history;
	char *lines[] = {"Ae\n", "one more\n", "And a last one!\n", NULL};
	int history_fd, i;

	/* Allocate memory for history node */
	history = malloc(sizeof(char *) * HISTSIZE + 1);

	/* Get history array and history fd */
	history_fd = get_history(history);

	/* history_fd should be a non-negative file descriptor */
	printf("history_fd: %d\n", history_fd);

	/* Save my fake lines to history */
	for (i = 0; lines[i]; i++)
		save_line_to_history(lines[i], history, history_size);

	/* Let's test builtin_history. We'll need a command node */
	*node = command_node_init("history", NULL);
	node->args = history;

	/* Print history - should print history file + my fake lines*/
	builtin_history(node);

	/* Save history to file */
	save_history_to_file(history, history_fd, history_size);

	/* Okay, now go make sure your fake lines got saved into the file */
	return (0);
}
