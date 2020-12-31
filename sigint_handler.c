#include "shell.h"

/**
 * sigint_handler - handles SIGINT (CTRL-C) signal for shell
 * @signum: signal number caught by signal, 2 for SIGINT
 **/
void sigint_handler(int signum)
{
	(void)signum;

	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, shell.prompt, _strlen(shell.prompt));
}
