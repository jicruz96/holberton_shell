#include "shell.h"

/**
 * execute_file - executes a file line by line
 * @fd: file descriptor
 * Return: exit status
 **/ 
int execute_file(int fd)
{
	/* We can deal with the 'empty prompt' issue much more cleanly this way */
	char *prompt = get_prompt(fd);
	char **history;
	FILE *fp = fdopen(fd, 'r');
	exec_f executor = NULL;

	if (fd == STDIN_FILENO)
	{
		sprintf(history_path, "%s/%s", homedir, ".hsh_history");
		free(homedir);
		history_fd = open(history_path, O_CREAT | O_RDWR | O_APPEND);
		history_line_no = get_history(history);
	}

	/* we may be better off using our own getline, come to think of it */
	while (getline(&line, &line_size, fp) != -1)
	{
		/* this is just the expanded-out version of what we wrote in the
		commented-out section below */
		args = tokenize(line);
		command = make_commands(args);
		for (tmp = command; tmp; tmp = tmp->next)
		{
			if (strcmp(tmp->command, "history") == 0)
				tmp->args = history;
			/* I made a typedef for a function pointer: typedef int exec_f(command_t *command);
			That typedef means pointer to a function of type "exec_f", defined as a function that takes
			a command struct ptr as an input and returns an integer (exit status) as an output
			get_executor() can use the command's logic to choose an executor (builtin function, wrapped execve,
			piped execs, etc) and return a pointer to that function */
			executor = get_executor(command);
			status = executor(tmp);
			if (fd == STDIN_FILEOUT)
				save_to_history(line, history);
			/* Logic about operators and exit statuses goes here probably */
		}
		free_everything(command);
	}
	/*
	   while ((line = getline()) != -1):
		args = tokenize(line);
		commands = make_commands(args)
		for command in commands:
			status = execute(command)
			save_history()
	*/
	return (0);
}
