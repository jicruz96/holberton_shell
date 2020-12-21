#include "shell.h"
/**
 * execute_hshrc - executes the .hshrc file if it exists
 * Return: exit status of execute_file()
 **/
int execute_hshrc(void)
{
    int hshrc_fd;
    char *homedir, path[256];

    /* create path for hshrc */
    homedir = getenv("HOME");
    sprintf(path, %s/%s, homedir, ".hshrc");
    free(homedir);

    /* go get .hshrc file descriptor */
    hshrc_fd = get_file_descriptor(path);
    if (hshrc_fd == -1)
        return (-1);
    
    return (execute_file(hshrc_fd, ""));
}

int execute_arg(char *filename)
{
    int fd;

    if (filename == NULL)
        return (-1);

    fd = get_file_descriptor(filename);
    if (fd == -1)
        return (-1);
    
    return (execute_file(fd, ""));
}