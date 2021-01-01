#include "shell.h"

/**
 * _realloc - custom realloc
 * @p: pointer
 * @size: new size
 * Return: p
 **/
char *_realloc(char *p, int size)
{
	char *new;
	int i;

	if (!p)
		return (malloc(sizeof(char) * size));

	new = malloc(sizeof(char) * size);
	for (i = 0; p[i] && i < size; i++)
		new[i] = p[i];
	free(p);
	return (new);
}
