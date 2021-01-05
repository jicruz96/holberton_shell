#include "../shell.h"
#define setenv(x) builtin_setenv(x)
/**
 * builtin_cd - custom cd (i.e. "change directory") built-in
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_cd(char **args)
{
	char *home, *prev_dir, *c = malloc(sizeof(char) * 256);
	char *prg = malloc(10), *z[] = {NULL, NULL, NULL}, *a = "PWD";

	z[1] = prg;
	if (args[1] == NULL)
	{
		home = _getenv("HOME"), _strcpy(z[1], "OLDPWD"), z[2] = getcwd(c, 256);
		if (chdir(home) == -1)
		{
			free(c), free(home), free(prg);
			return (handle_error(CD_FAIL, "cd", home));
		}
		setenv(z), _strcpy(z[1], "PWD"), z[2] = home, setenv(z);
		free(home), free(c), free(prg);
		return (EXIT_SUCCESS);
	}
	if (args[1][0] == '-')
	{
		prev_dir = _getenv("OLDPWD");
		if (!prev_dir || !(*prev_dir))
			free(prev_dir), prev_dir = _getenv("HOME");
		_strcpy(z[1], "OLDPWD"), z[2] = getcwd(c, 256);
		if (chdir(prev_dir) == -1)
		{
			free(c), free(prev_dir), free(prg);
			return (handle_error(CD_FAIL, "cd", prev_dir));
		}
		printf("%s\n", prev_dir);
		setenv(z), _strcpy(z[1], "PWD"), z[2] = prev_dir, setenv(z);
		free(prev_dir), free(c), free(prg);
		return (EXIT_SUCCESS);
	}
	_strcpy(z[1], "OLDPWD"), z[2] = getcwd(c, 256);
	if (chdir(args[1]) == -1)
	{
		free(c), free(prg);
		return (handle_error(CD_FAIL, "cd", _strdup(args[1])));
	}
	setenv(z), _strcpy(z[1], a), z[2] = args[1], setenv(z), free(c), free(prg);
	return (EXIT_SUCCESS);
}
