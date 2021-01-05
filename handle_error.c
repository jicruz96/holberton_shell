#include "shell.h"

/**
 * handle_error - prints error messages
 * @code: error code
 * Return: error code
 **/
int handle_error(int code)
{
	char error_msg[256];

	sprintf(error_msg, "%s: %d", shell.name, shell.lines);
	perror(error_msg);
	return (code);
}
