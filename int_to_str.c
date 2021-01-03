#include "shell.h"

/**
 * int_to_str - returns string representation of int
 * @n: number
 * Return: string rep of n
 **/
char *int_to_str(int n)
{
	char *s = _realloc(NULL, sizeof(char) * 12);

	sprintf(s, "%d", n);
	return (s);
}
