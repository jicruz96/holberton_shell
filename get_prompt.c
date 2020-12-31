#include "shell.h"

/**
 * get_prompt - returns the prompt, a formatted string
 * @fd: file descriptor. determines what prompt is returned
 * Return: Prompt
 */
char *get_prompt(int fd)
{
	/* does fd refer to a terminal? yes? return prompt. else, empty str */
	return (isatty(fd) ? "shell: " : "");
}
