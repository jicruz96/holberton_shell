#include "shell.h"
/**
 * command_node_init - inits new command node
 * @command: command that the node represent
 * Return: New node
 */
command_t *command_node_init(char *command)
{
	command_t *new = malloc(sizeof(command_t));

	if (!new)
		return (NULL);
	new->logic = DEFAULT_LOGIC;
	new->command = command;
	new->path = get_program_path(command);
	new->executor = get_executor(command);
	new->heredoc = NULL;
	new->input = NULL;
	new->output = NULL;
	new->args = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}



/**
 * execute_command - wrapper for execve
 * @path: command path
 * @args: command args
 * Return: status
 **/
int execute_command(char *path, char **args)
{
	return (execve(path, args, environ));
}
