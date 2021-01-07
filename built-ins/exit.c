#include "../shell.h"

/**
 * builtin_exit - custom exit built-in
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_exit(char **args)
{
	int status = 0, i = 0;

	/* Check for numeric exit code */
	if (args[1])
	{
		/* If exit code is invalid, print error */
		for (i = 0; args[1][i]; i++)
			if (!IS_NUMERIC(args[1][i]))
				return (handle_error(EXIT_ERROR, "exit", _strdup(args[1])));

		/* Else, calculate exit code */
		for (i = 0; args[1][i]; i++)
			status = 10 * status + (args[1][i] - '0');
	}
	else
	{
		status = shell.status;
	}

	/* set shell.run = false */
	shell.run = false;

	/* Return exit code */
	return (status);
}
