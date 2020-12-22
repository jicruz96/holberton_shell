#include "shell.h"
/**
 * command_node_init - inits new command node
 * @path: program path
 * @command: command that the node represent
 * Return: New node
 */ 
command_t *command_node_init(char *path, char *command)
{
	command_t *new = malloc(sizeof(command_t));

	if (!new)
		return (NULL);
	new->logic = DEFAULT;
	new->path = path;
	new->command = command;
	new->input_no = STDIN_FILENO;
	new->output_no = STDOUT_FILENO;
	new->input = NULL;
	new->output = NULL;
	new->args = NULL;
	new->next = NULL;
	new->prev= NULL;
	return (new);
}
