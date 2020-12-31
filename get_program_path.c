#include "shell.h"

/**
 * get_program_path - finds a program in the PATH
 * @program: program name (char *)
 * Return: full program path || just program if not found in path
 **/
char *get_program_path(char *program)
{
	int i, j;
	char *buffer;
	char *PATH, **paths, *path;
	char *builtins[] = {"cd", "help", "alias", "setenv", "unsetenv", "exit", "history", "env", NULL};


	/* If program is builtin, don't search path, just return copy of program */
	for (i = 0; builtins[i]; i++)
		if (_strcmp(builtins[i], program) == 0)
			return (_strdup(program));

	/* store the path in a variable */
	PATH = _getenv("PATH");

	/* make space for paths array and buffer */
	paths = malloc(sizeof(char *) * 100);
	buffer = malloc(sizeof(char) * 256);

	/* get the first path */
	path = strtok(PATH, ":");

	/* concat the path with a / and the program name */
	sprintf(buffer, "%s/%s", path, program);

	/* store our full program path into the path array */
	paths[0] = buffer;

	/* get the rest of the PATH */
	for (i = 1; (path = strtok(NULL, ":"));)
	{
		/* same thing, make a slash and the program name at the end of path */
		sprintf(buffer, "%s/%s", path, program);
		/* add the path to the paths array */
		paths[i++] = strdup(buffer);
	}
	/* Check all the paths */
	for (i = 0; paths[i]; i++)
	{
		/* check to see if we can execute this file */
		if (access(paths[i], X_OK) == 0)
		{
			/* free all excess paths */
			for (j = i + 1; paths[j]; j++)
				free(paths[j]);
			/* return the path */
			return (paths[i]);
		}
		free(paths[i]);
	}
	/* If no paths worked and if it's not a builtin, then return program */
	return (program);
}
