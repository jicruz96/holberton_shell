#include "../shell.h"

/**
 * builtin_env- custom env built-in. prints environment variables
 * @path: path (string)
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_env(char *path, char **args)
{
	int i;

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);

	return (0);
}

/**
 * builtin_setenv - custom setenv built-in. sets new environment variable
 * @path: path (string)
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_setenv(char *path, char **args)
{
    int status = 0;
    
    return (status);
}

/**
 * builtin_unsetenv- custom unsetenv built-in. deletes environment variable
 * @path: path (string)
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_unsetenv(char *path, char **args)
{
    int status = 0;
    
    return (status);
}
