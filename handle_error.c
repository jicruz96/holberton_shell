#include "shell.h"

/**
 * handle_error - prints error messages
 * @code: error code
 * @program: program that failed
 * @supplement: supplement text
 * Return: error code
 **/
int handle_error(int code, char *program, char *supplement)
{
	char ugh[256];
	code_t codes[] = {{ENOENT, 127, "not found"},
					  {EACCES, 126, "Permission denied"},
					  {CD_FAIL, 2, "can't cd to %s"},
					  {EXIT_ERROR, 2, "Illegal number: %s"},
					  {UNSETENV_FAIL, 1, "Too few arguments."},
					  {SETENV_FAIL, 1, "Variable name must contain alphanumeric characters."},
					  {SETENV2, 1, "Variable name must begin with a letter"},
					  {0, 0, NULL}};
	int i;
	char *str = "%s: %d: %s: %s\n";

	for (i = 0; codes[i].msg; i++)
		if (code == codes[i].code)
		{
			if (supplement)
				sprintf(ugh, codes[i].msg, supplement);
			else
				_strcpy(ugh, codes[i].msg);

			dprintf(STDERR_FILENO, str, shell.name, shell.lines, program, ugh);
			free(supplement);
			return (codes[i].shell_code);
		}

	sprintf(ugh, "%s: %d: %s", shell.name, shell.lines, program);
	perror(ugh);
	free(supplement);
	return (code);
}
