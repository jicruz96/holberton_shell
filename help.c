#include "shell.h"

/**
 * help_help - helps help help
 **/
void help_help(void)
{
	int i;
	char *lines[] = {
		"help: help [builtin]",
		"\tDisplay helpful information about builtin commands.",
		NULL
	};
	
	for (i = 0; lines[i]; i++)
		_puts(lines[i]);
}

/**
 * builtin_help - custom help builtin
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_help(char **args)
{
	int status = 0, i;

	if (args[1] == NULL)
	{
		printf("usage: help [builtin]\n");
		return (1);
	}

	for (i = 1; args[i]; i++)
	{
		if (_strcmp(args[i], "alias") == 0)
			help_alias();
		else if (_strcmp(args[i], "history") == 0)
			help_history();
		else if (_strcmp(args[i], "exit") == 0)
			help_exit();
		else if (_strcmp(args[i], "cd") == 0)
			help_cd();
		else if (_strcmp(args[i], "help") == 0)
			help_help();
		else
			status = help_environment(args[i]);
	}
	return (status);
}
