#include "shell.h"

/**
 * fork_and_exec - forks and executes
 * @cmd: command node
 **/
void fork_and_exec(command_t *cmd)
{
	pid_t child_pid;
	int status = 0;

	if (cmd->path || cmd->executor)
	{
		child_pid = fork();
		if (child_pid == 0) /* child executes */
		{
			if (cmd->executor)
				shell.status = cmd->executor(cmd->args);
			else
				shell.status = execve(cmd->path, cmd->args, environ);

			if (shell.status)
				exit(handle_error(errno, cmd->command, NULL));
			exit(shell.status);
		}
		/* Parent waits (or detects forking error) */
		if (child_pid == -1 || waitpid(child_pid, &status, 0) == -1)
			shell.status = handle_error(errno, cmd->command, NULL);
		else
			shell.status = WEXITSTATUS(status);
	}
	else
		shell.status = handle_error(shell.status, cmd->command, NULL);
}

/**
 * get_output_fd - gets output fd
 * @cmd: command node
 * Return: output file descriptor
 **/
int get_output_fd(command_t *cmd)
{
	int fd, perms;
	char error_msg[256], *str = "%s: %d: cannot open %s: ";

	if (cmd->logic & (IS_REDIR_OUT | IS_APPEND))
	{
		if (cmd->output == NULL)
		{
			fd = handle_syntax_error(cmd->logic & IS_APPEND ? ">>" : ">");
			shell.status = fd; /* this just exists to get prev line under 80 */
			return (-1);
		}
		if (cmd->logic & IS_APPEND)
			perms = O_CREAT | O_RDWR | O_APPEND;
		else
			perms = O_CREAT | O_RDWR | O_TRUNC;

		fd = open(cmd->output, perms, 0644);
		if (fd == -1)
		{
			shell.status = 2;
			sprintf(error_msg, str, shell.name, shell.lines, cmd->output);
			if (errno == ENOENT)
				_strcat(error_msg, "No such file\n");

			else
				_strcat(error_msg, "Permission denied\n");
			write(STDERR_FILENO, error_msg, _strlen(error_msg));
			return (-1);
		}
		return (fd);
	}
	return (STDOUT_FILENO);
}

/**
 * get_input_fd - get input fd
 * @cmd: command node
 * Return: input file descriptor
 **/
int get_input_fd(command_t *cmd)
{
	int pipefds[2], fd;
	char error_msg[256], *str = "%s: %d: cannot open %s: ";

	if (cmd->logic & IS_REDIR_IN)
	{
		if (cmd->input == NULL)
		{
			shell.status = handle_syntax_error("<");
			return (-1);
		}

		fd = open(cmd->input, O_RDONLY);
		if (fd == -1)
		{
			shell.status = 2;
			sprintf(error_msg, str, shell.name, shell.lines, cmd->input);
			if (errno == ENOENT)
				_strcat(error_msg, "No such file\n");
			else
				_strcat(error_msg, "Permission denied\n");
			write(STDERR_FILENO, error_msg, _strlen(error_msg));
			return (-1);
		}
		return (fd);
	}

	if ((cmd->logic & IS_HEREDOC) && cmd->args[1] == NULL)
	{
		/* make pipe for heredoc */
		pipe(pipefds);
		/* write contents onto pipe */
		if (cmd->input)
			write(pipefds[1], cmd->input, _strlen(cmd->input));
		/* close writing side of pipe */
		close(pipefds[1]);
		/* set input to reading side of pipe */
		return (pipefds[0]);
	}

	return (STDIN_FILENO);
}
