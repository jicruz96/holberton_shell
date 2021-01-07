#include "../shell.h"

/**
 * builtin_cd - custom cd (i.e. "change directory") built-in
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_cd(char **args)
{
	char cwd[256], *OLDPWD[] = {0, "OLDPWD", 0}, *new[] = {0, "PWD", 0};
	int print_dir = 0;

	/* set OLDPWD to current working directory */
	OLDPWD[2] = getcwd(cwd, 256);

	/* set new directory target */
	if (_strcmp(args[1], "-") == 0)
		new[2] = _getenv("OLDPWD"), print_dir = true;
	else
		new[2] = _strdup(args[1]);

	/* if no dir found/provided, change to home dir */
	if (!new[2] || !new[2][0])
		free(new[2]), new[2] = _getenv("HOME");

	/* if no home dir found, just stay in cwd! */
	if (!new[2] || !new[2][0])
		free(new[2]), new[2] = OLDPWD[2];

	/* change directory */
	if (chdir(new[2]) == -1)
		return (handle_error(CD_FAIL, "cd", new[2]));

	if (print_dir)
		printf("%s\n", new[2]);

	/* update environment */
	builtin_setenv(OLDPWD), builtin_setenv(new);

	/* free new[2] if it points to malloc'd memory */
	if (new[2] != OLDPWD[2])
		free(new[2]);

	return (EXIT_SUCCESS);
}
