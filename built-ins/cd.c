#include "../shell.h"

/**
 * builtin_cd - custom cd (i.e. "change directory") built-in
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_cd(char **args)
{
	char *home, *prev_dir;

	/* if no directory was input cd $HOME */
	if (args[1] == NULL)
	{
		home = _getenv("HOME");
		if (chdir(home) == -1)
		{
			free(home);
			return (handle_error(CD_FAIL));
		}
		free(home);
		return (EXIT_SUCCESS);
	}

	if (args[1][0] == '-')
	{
		prev_dir = _getenv("OLDPWD");
		if (!prev_dir || !(*prev_dir))
		{
			free(prev_dir);
			return (handle_error(NO_OLD_PWD));
		}
		if (chdir(prev_dir) == -1)
		{
			free(prev_dir);
			return (handle_error(CD_FAIL));
		}
		return (EXIT_SUCCESS);
	}

	/* otherwise, change dir, if it fails, return CD_FAIL ... */
	if (chdir(args[1]) == -1)
		return (handle_error(CD_FAIL));
	return (EXIT_SUCCESS);
}
