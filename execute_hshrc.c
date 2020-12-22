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
	hshrc_fd = open(path, O_RDONLY);
	if (hshrc_fd == -1)
		return (-1);
	
	return (execute_file(hshrc_fd));
}

/**
 * execute_arg - executes argument to shell
 * @argv: argument array
 * Return: exit status
 **/
int execute_arg(char *argv[])
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		sprintf(error_msg, "%s: %s", argv[0], argv[1]);
		perror(error_msg);
		return (errno);
	}   
	return (execute_file(fd));
}
