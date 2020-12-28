#include "shell.h"

/**
 * sigint_handler - handles SIGINT (CTRL-C) signal for shell
 * @signum: signal number caught by signal, 2 for SIGINT
 **/
void sigint_handler(int signum)
{
	if (signum == 2)
		printf("\n$ ");
}
