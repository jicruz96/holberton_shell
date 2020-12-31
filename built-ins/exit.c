#include "../shell.h"


/**
 * clean_and_exit - custom exit built-in
 * @path: path (string)
 * @args: arguments (string array)
 * Return: exit status
 **/
int builtin_exit(char *path, char **args)
{
    int status = 0;

    (void)path;

    if (args[1])
    {
        for (i = 0; args[1][i]; i++)
            if (!IS_NUMERIC(args[i][1]))
                return (handle_error(EXIT_ERROR));
        
        for (i = 0; args[1][i]; i++)
            status = 10 * status + (args[1][i] - '0');
    }
    
    shell.run = false;
    return (status);
}
