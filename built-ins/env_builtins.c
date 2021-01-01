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
		printf("%s\n", environ[i]);

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
	int status = 0;

	(void)args;
	return (status);
}

/**
 * builtin_unsetenv- custom unsetenv built-in. deletes environment variable
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_unsetenv(char **args)
{
	int status = 0;

	(void)args;
	return (status);
}
