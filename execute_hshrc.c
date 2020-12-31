#include "shell.h"
/**
 * execute_hshrc - executes the .hshrc file if it exists
 * Return: exit status of execute_file()
 **/
void execute_hshrc(void)
{
	int hshrc_fd;
	char *homedir, path[256];

	/* create path for hshrc */
	homedir = _getenv("HOME");
	sprintf(path, "%s/%s", homedir, ".hshrc");
	free(homedir);

	/* go get .hshrc file descriptor */
	hshrc_fd = open(path, O_RDONLY);
	if (hshrc_fd == -1)
		return;

	execute_file(hshrc_fd);
}
