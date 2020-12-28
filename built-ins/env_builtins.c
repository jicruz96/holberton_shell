#include "../shell.h"

/**
 * builtin_env- custom env built-in. prints environment variables
 * @command: command node
 * Return: exit status
 **/
int builtin_env(command_t *command)
{
	int i;

	for (i = 0; environ[i]; i++)
		dprintf(command->output, "%s\n", environ[i]);

	return (0);
}

/**
 * builtin_setenv - custom setenv built-in. sets new environment variable
 * @command: command node
 * Return: exit status
 **/
int builtin_setenv(command_t *command)
{
    int status;
    
    return (status);
}

/**
 * builtin_unsetenv- custom unsetenv built-in. deletes environment variable
 * @command: command node
 * Return: exit status
 **/
int builtin_unsetenv(command_t *command)
{
    int status;
    
    return (status);
}
