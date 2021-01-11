#include "../shell.h"

/**
 * builtin_env- custom env built-in. prints environment variables
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_env(char **args)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	(void)args;
	return (0);
}

/**
 * builtin_setenv - custom setenv built-in. sets new environment variable
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_setenv(char **args)
{
	int i;
	char *ENV_VAR;
	char *VARIABLE, *VALUE, *var = NULL;

	/* if only "setenv" passed in, call env */
	if (args[1] == NULL || args[2] == NULL)
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 29);
		return (1);
	}

	/* retrieve our env variable and new corresponding value */
	VARIABLE = args[1];
	VALUE = args[2];

	/* construct env var */
	ENV_VAR = malloc(sizeof(char) * 256);
	sprintf(ENV_VAR, "%s=%s", VARIABLE, VALUE);

	/* loop through enviornment variables */
	for (i = 0; environ[i]; i++)
	{
		var = _strdup(environ[i]);
		if (_strcmp(strtok(var, "="), VARIABLE) == 0)
		{
			free(var), free(environ[i]);
			environ[i] = ENV_VAR;
			return (EXIT_SUCCESS);
		}
		free(var);
	}
	/* set environ [i] to our new env var if it's NULL */
	environ = _realloc_string_array(environ, 1);
	environ[i] = ENV_VAR;
	return (EXIT_SUCCESS);
}

/**
 * builtin_unsetenv- custom unsetenv built-in. deletes environment variable
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_unsetenv(char **args)
{
	int i, j;
	char *UNSET_VARIABLE, *var;

	/* if no arguments were given, print error */
	if (args[1] == NULL)
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 25);
		return (1);
	}

	UNSET_VARIABLE = args[1];

	for (i = 0; environ[i]; i++)
	{
		var = _strdup(environ[i]);

		/* if the environment variable matches the target... */
		if (_strcmp(strtok(var, "="), UNSET_VARIABLE) == 0)
		{
			free(var);
			free(environ[i]);
			/* adjust the environment array */
			for (j = i + 1; environ[j]; i++, j++)
				environ[i] = environ[j];

			/* null-terminate the environment array */
			environ[i] = NULL;
			return (EXIT_SUCCESS);
		}
		free(var);
	}
	return (EXIT_SUCCESS);
}
