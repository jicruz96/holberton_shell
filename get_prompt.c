#include "shell.h"

/**
 * get_prompt - returns the prompt, a formatted string
 * @fd: file descriptor. determines what prompt is returned
 * Return: Prompt
 */
char *get_prompt(int fd)
{
	int i, j;
	char *prompt, *str = NULL, *tmp = NULL;
	format_match_t matchers[] = {{'d', &get_date_prompt},
								 {'H', &get_hostname_prompt},
								 {'s', &get_shellname_prompt},
								 {'u', &get_username_prompt},
								 {'w', &get_cwd_prompt},
								 {'\0', NULL}};

	if (!isatty(fd))
		return (_strdup(""));

	prompt = _getenv("PS1");
	if (!prompt || !(*prompt))
	{
		free(prompt);
		return (_strdup("$ "));
	}

	for (i = 0; prompt[i]; i++)
		if (prompt[i] == '\\')
			for (j = 0; matchers[j].formatter; j++)
				if (matchers[j].specifier == prompt[i + 1])
				{
					str = matchers[j].formatter();
					tmp = _realloc(tmp, _strlen(str) + _strlen(prompt) - 1);
					sprintf(tmp, "%.*s%s%s", i, prompt, str, prompt + i + 2);
					free(prompt);
					free(str);
					prompt = _strdup(tmp);
					free(tmp);
					tmp = NULL;
					i -= 1;
				}

	return (prompt);
}
