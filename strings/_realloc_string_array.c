#include "../shell.h"

/**
 * _realloc_string_array - does what it sounds like
 * @array: array
 * @is_malloced: determines whether inserted array must be freed
 * Return: reference to new chunk
 **/
char **_realloc_string_array(char **array, int is_malloced)
{
	char **new = NULL;
	int i;

	if (!array)
	{
		new = malloc(sizeof(char *));
		*new = NULL;
		return (new);
	}

	for (i = 0; array[i]; i++)
		;

	new = malloc(sizeof(array) * (i + 2));
	for (i = 0; array[i]; i++)
	{
		new[i] = _strdup(array[i]);
		if (is_malloced)
		{
			free(array[i]);
		}
	}
	new[i] = NULL;
	new[i + 1] = NULL;
	if (is_malloced)
		free(array);
	return (new);
}
