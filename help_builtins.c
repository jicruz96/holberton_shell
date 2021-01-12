#include "shell.h"

/**
 * help_alias - prints alias help content
 **/
void help_alias(void)
{
	int i;
	char *lines[] = {
		"alias: alias [name[=value] ... ]",
		"\t`alias' with no arguments prints the list of aliases in the",
		"\tof aliases in the form alias NAME=VALUE on standard output.",
		"\tOtherwise, an alias is defined for each NAME whose VALUE is given.",
		"\tA trailing space in VALUE causes the next word to be checked for",
		"\talias substitution when the alias is expanded.  Alias returns",
		"\ttrue unless a NAME is given for which no alias has been defined.",
		NULL
	};

	for (i = 0; lines[i]; i++)
		_puts(lines[i]);
}

/**
 * help_cd - prints cd help content
 **/
void help_cd(void)
{
	int i;
	char *lines[] = {
	"cd: cd [dir]",
	"\tChange the current directory to DIR.  The variable $HOME is the",
	"\tdefault DIR. If DIR is `-', then cd to the value of $OLDPWD",
	NULL
	};

	for (i = 0; lines[i]; i++)
		_puts(lines[i]);
}

/**
 * help_environment - prints environment help content
 * @builtin: builtin
 * Return: 1 if case isn't recognized | 0 on success
 **/
int help_environment(char *builtin)
{
	int i;
	char *setenv_lines[] = {
		"setenv: setenv [VARIABLE] [VALUE]",
		"\tUpdate, or set a new enviornment variable.",
		"\tIf called with no arguements, a list of all",
		"\tenviornment variables will be printed, see env.",
		NULL
	};
	char *env_lines[] = {
		"env: env",
		"\tPrint a list of the enviornment.",
		NULL
	};
	char *unsetenv_lines[] = {
		"unsetenv: unsetenv [VARIABLE]",
		"\tDeletes an environment variable",
		NULL
	};
	char error_msg[256], *str = "%s: %s: no help topics match %s\n";

	if (_strcmp(builtin, "setenv") == 0)
		for (i = 0; setenv_lines[i]; i++)
			_puts(setenv_lines[i]);

	else if (_strcmp(builtin, "unsetenv") == 0)
		for (i = 0; unsetenv_lines[i]; i++)
			_puts(unsetenv_lines[i]);

	else if (_strcmp(builtin, "env") == 0)
		for (i = 0; env_lines[i]; i++)
			_puts(env_lines[i]);

	else
	{
		sprintf(error_msg, str, shell.name, shell.lines, builtin);
		write(STDERR_FILENO, error_msg, _strlen(error_msg));
		return (1);
	}

	return (0);
}

/**
 * help_history - prints history help content
 **/
void help_history(void)
{
	int i;
	char *lines[] = {
		"history:",
		"\tPrints history",
		NULL
	};

	for (i = 0; lines[i]; i++)
		_puts(lines[i]);
}

/**
 * help_exit - prints help exit content
 **/
void help_exit(void)
{
	int i;
	char *lines[] = {
		"exit: exit",
		"\tExits the shell.",
		NULL
	};

	for (i = 0; lines[i]; i++)
		_puts(lines[i]);
}
