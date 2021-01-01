#include "../shell.h"

/**
 * builtin_history - custom history built-in
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_history(char **args)
{
	int i;

	(void)args;
	for (i = 0; shell.history[i]; i++)
		printf("%5d  %s", i, shell.history[i]);

	return (0);
}
