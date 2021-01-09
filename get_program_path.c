#include "shell.h"

/**
 * get_program_path - finds a program in the PATH
 * @program: program name (char *)
 * Return: full program path || just program if not found in path
 **/
char *get_program_path(char *program)
{
	int i;
	char *PATH, *path = NULL, *buffer = NULL;
	char *builtins[] = {"cd", "help", "alias", "setenv", "unsetenv", "exit",
						"history", "env", NULL};

	/* If program is a path, return copy of program */
	for (i = 0; program[i]; i++)
		if (program[i] == '/')
			return (_strdup(program));

	/* If program is builtin or, return copy of program */
	for (i = 0; builtins[i]; i++)
		if (_strcmp(builtins[i], program) == 0)
			return (_strdup(program));

	PATH = _getenv("PATH");
	buffer = malloc(sizeof(char) * 256);

	/* check the PATH */
	while ((path = strtok((path ? NULL : PATH), ":")))
	{
		/* concat path with slash and program name */
		sprintf(buffer, "%s/%s", path, program);
		if (access(buffer, X_OK) == 0)
		{
			free(PATH);
			return (buffer);
		}
	}

	free(PATH);
	free(buffer);
	return (NULL);
}
