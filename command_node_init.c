#include "shell.h"
/**
 * command_node_init - inits new command node
 * @command: command that the node represent
 * Return: New node
 */
command_t *command_node_init(char *command)
{
	int i;
	command_t *new = malloc(sizeof(command_t));

	if (!new)
		return (NULL);

	command = get_alias(command);
	new->logic = DEFAULT_LOGIC;
	new->command = command;
	new->path = get_program_path(command);
	new->executor = get_executor(command);
	new->extra_fd = 0;
	new->input = NULL;
	new->output = NULL;
	new->args = malloc(sizeof(char *) * 256);
	new->args[0] = command;
	for (i = 1; i < 256; i++)
		new->args[i] = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
