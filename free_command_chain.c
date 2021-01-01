#include "shell.h"

/**
 * free_command_chain - free command structs before exiting
 * @head: head of command linked list
 **/
void free_command_chain(command_t *head)
{
	int i;

	/* Must free path and node itself */
	if (!head)
		return;

	free(head->path);
	free(head->input);
	free(head->output);
	if (head->args)
		for (i = 0; head->args[i]; i++)
			free(head->args[i]);
	free(head->args);
	if (head->next)
		free_command_chain(head->next);
	free(head);
}
