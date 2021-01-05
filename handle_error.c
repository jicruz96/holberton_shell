#include "shell.h"

/**
 * handle_error - prints error messages
 * @code: error code
 * @supplement: supplement text
 * Return: error code
 **/
int handle_error(int code, char *program, char *supplement)
{
	char error_msg[256];
    code_t[] = {{ENOENT, 127, "not found"}, {EPERM, 1, "Permission denied"},\
                {CD_FAIL, 2, "can't cd to "}, {EXIT_ERROR, , "Illegal number: "},\
                {NO_OLD_PWD, , "No OLDPWD set"}
    }

	sprintf(error_msg, "%s: %d: %s", shell.name, shell.lines, program);

    if (code == ENOENT)
    {
        dprintf(STDERR_FILENO, "%s: not found\n", error_msg);
    }
    else if (code == CD_FAIL)
    {
        dprintf(STDERR_FILENO, "%s: something\n", error_msg);
    }
    else if (code == EXIT_ERROR)
    {
        dprintf(STDERR_FILENO, "%s: something\n", error_msg);
    }
    else if (code == EPERM)
    {
        dprintf(STDERR_FILENO, "%s: something\n", error_msg);
        
    }
    else if (code == NO_OLD_PWD)
    {
        dprintf(STDERR_FILENO, "%s: something\n", error_msg);
    }
    else if (code == TOO_PWD)
    {
        dprintf(STDERR_FILENO, "%s: something\n", error_msg);
    }
	else if (code == UNSETENV_FAIL)
	{
        dprintf(STDERR_FILENO, "%s: something\n", error_msg);
	}
    
	perror(error_msg);
	return (code);
}
