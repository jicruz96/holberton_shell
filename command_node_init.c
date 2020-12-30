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
	new->path = get_program_path(command);
	printf("\tnew command's path is %s\n", new->path);
	new->command = command;
	new->input_fd = STDIN_FILENO;
	new->output_fd = STDOUT_FILENO;
	new->line_no = 0;
	new->executor = get_executor(command);
	printf("\tnew command's executor is %p\n", new->executor);
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