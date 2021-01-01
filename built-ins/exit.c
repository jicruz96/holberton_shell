#include "../shell.h"

/**
 * builtin_exit - custom exit built-in
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_exit(char **args)
{
	int status = 0;
	int i;

	if (args[1])
	{
		for (i = 0; args[1][i]; i++)
			if (!IS_NUMERIC(args[1][i]))
				return (handle_error(EXIT_ERROR));

		for (i = 0; args[1][i]; i++)
			status = 10 * status + (args[1][i] - '0');
	}

	shell.run = false;

	return (status);
}
