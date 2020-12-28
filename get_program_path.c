#include "shell.h"

/**
 * get_program_path - finds a program in the PATH
 * @program: program name (char *)
 * Return: full program path || just program if not found in path
 **/
char *get_program_path(char *program)
{
	int i;
	char *buffer, *PATH, **path;

	/* store the path in a variable */
	PATH = getenv("PATH");

	/**
	 * make some space for each part of the path
	 * and for the buffer we will operate on */
	path = malloc(sizeof(char *) * 100);
	buffer = malloc(sizeof(char *) * 256);

	/* get the first path */
	buffer = strtok(PATH, ":");

	/* concat the path with a / and the program name */
	sprintf(buffer, "%s/%s", buffer, program);

	/* store our full program path into the path array */
	path[0] = buffer;

	i = 1;
	/* get the rest of the PATH */
	while ((buffer = strtok(NULL, ":")))
	{
		/* same thing, make a slash and the program name at the end of path */
		sprintf(buffer, "%s/%s", buffer, program);
		/* add the path to the paths array */
		path[i] = buffer;
		i++;
	}

	for (i = 0; path[i]; i++)
	{
		/* check to see if we can execute this file */
		if (access(path[i], X_OK))
			/* return the path */
			return (path[i]);
	}
	return (NULL);
}
