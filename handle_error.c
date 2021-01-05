#include "shell.h"

/**
 * handle_error - prints error messages
 * @code: error code
 * Return: error code
 **/
int handle_error(int code)
{
	char error_msg[256];
    code_t[] = {{ENOENT, 127, "not found"},
    }

	sprintf(error_msg, "%s: %d", shell.name, shell.lines);
    if (code == EINVAL)
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
    else if (code == EBADPERMS)
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
