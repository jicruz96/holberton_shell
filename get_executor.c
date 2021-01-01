#include "shell.h"

/**
 * get_executor - returns pointer to appropriate executor function
 * @command: command (as a string)
 * Return: function pointer
 **/
exec_f get_executor(char *command)
{
	/**
	 * If command is a built-in, return the corresponding
	 * built-in executor function
	 * Else, return regular execution function
	 */

	if (_strcmp("cd", command) == 0)
		return (&builtin_cd);
	else if (_strcmp("help", command) == 0)
		return (&builtin_help);
	else if (_strcmp("env", command) == 0)
		return (&builtin_env);
	else if (_strcmp("setenv", command) == 0)
		return (&builtin_setenv);
	else if (_strcmp("history", command) == 0)
		return (&builtin_history);
	else if (_strcmp("unsetenv", command) == 0)
		return (&builtin_unsetenv);
	else if (_strcmp("alias", command) == 0)
		return (&builtin_alias);
	else if (_strcmp("exit", command) == 0)
		return (&builtin_exit);

	return (NULL);
}
