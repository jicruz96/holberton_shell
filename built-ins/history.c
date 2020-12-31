#include "../shell.h"

/**
 * builtin_history - custom history built-in
 * @path: path (string)
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_history(char **args)
{
	int i;

	for (i = 0; args[i]; i++)
		printf("%5d  %s", i, args[i]);

	return (0);
}
