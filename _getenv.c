#include "shell.h"

/**
 * _getenv - returns value of env var
 * @key: env var
 * Return: value of env var
 */
char *_getenv(char *key)
{
	int i;
	int key_len = _strlen(key);

	for (i = 0; environ[i]; i++)
	{
		if (_strlen(environ[i]) < key_len)
			continue;

		if (strncmp(key, environ[i], key_len))
			continue;

		if (environ[i][key_len] != '=')
			continue;

		return (environ[i] + key_len + 1);
	}

	return (NULL);
}
