#include "../shell.h"

/**
 * builtin_history - custom history built-in
 * @command: command node
 * Return: exit status
 **/
int builtin_history(command_t *command)
{
	int i;

	for (i = 0; command->args[i]; i++)
		printf("%5d  %s", i, command->args[i]);

	return (0);
}
