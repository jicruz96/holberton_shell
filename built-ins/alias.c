#include "../shell.h"

/**
 * get_alias - returns alias of a token (or token itself if no alias)
 * @alias: alias
 * Return: alias value
 **/
char *get_alias(char *alias)
{
	alias_t *tmp = shell.aliases;

	if (shell.aliases)
		for (; tmp; tmp = tmp->next)
			if (_strcmp(alias, tmp->alias) == 0)
			{
				free(alias);
				return (_strdup(tmp->value));
			}

	return (alias);
}

/**
 * builtin_alias - builds alias and adds to alias struct
 * @args: args
 * Return: status
 */
int builtin_alias(char **args)
{
	int i = 0, j, status = 0;
	alias_t *tmp = shell.aliases;
	char *error_msg = "%s: %s: not found\n";

	if (args[1] == NULL)
		while (tmp)
		{
			printf("%s='%s'\n", tmp->alias, tmp->value);
			tmp = tmp->next;
		}
	else
		for (i = 1; args[i]; i++)
		{
			for (j = 0; args[i][j]; j++)
				if (args[i][j] == '=')
					break;
			if (args[i][j] == '=') /* i.e. ('command=value') */
			{

				/* search through alias list */
				for (tmp = shell.aliases; tmp; tmp = tmp->next)
					if (_strncmp(tmp->alias, args[i], j) == 0)
						break;

				if (!tmp)
				{
					tmp = malloc(sizeof(alias_t));
					tmp->alias = _strndup(args[i], j);
					tmp->next = shell.aliases, shell.aliases = tmp;
				}
				tmp->value = _strdup(args[i] + j + 1);
			}
			else
			{
				/* search through alias list */
				for (tmp = shell.aliases; tmp; tmp = tmp->next)
					if (_strcmp(tmp->alias, args[i]) == 0)
						break;

				if (tmp)
					printf("%s='%s'\n", tmp->alias, tmp->value);
				else /* if not found, print error */
				{
					dprintf(STDERR_FILENO, error_msg, *args, args[i]);
					status = 1;
				}
			}
		}
	return (status);
}
