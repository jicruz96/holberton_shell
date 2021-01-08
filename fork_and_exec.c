#include "shell.h"

/**
 * fork_and_exec - forks and executes
 * @cmd: command node
 **/
void fork_and_exec(command_t *cmd)
{
	pid_t child_pid;
	int status = 0;

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

/**
 * get_output_fd - gets output fd
 * @cmd: command node
 * Return: output file descriptor
 **/
int get_output_fd(command_t *cmd)
{
	if (cmd->output)
	{
		if (cmd->logic & IS_APPEND)
			return (open(cmd->output, O_CREAT | O_RDWR | O_APPEND, 0644));

		return (open(cmd->output, O_CREAT | O_RDWR | O_TRUNC, 0644));
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
	int pipefds[2];

	if (cmd->logic & IS_REDIR_IN)
		return (open(cmd->input, O_RDONLY));

	if ((cmd->logic & IS_HEREDOC) && cmd->args[1] == NULL)
	{
		/* make pipe for heredoc */
		pipe(pipefds);

		/* write contents onto pipe */
		write(pipefds[1], cmd->input, _strlen(cmd->input));

		/* close writing side of pipe */
		close(pipefds[1]);

		/* set input to reading side of pipe */
		return (pipefds[0]);
	}

	return (STDIN_FILENO);
}

/**
 * clean_pipes - clean pipes
 * @cmd: cmd
 * @input_fd: input fd
 * @output_fd: output_fd
 **/
void clean_pipes(command_t *cmd, int *input_fd, int *output_fd)
{
	if (*input_fd > 2)
		close(*input_fd);
	if (*output_fd > 2)
		close(*output_fd);

	*input_fd = STDIN_FILENO;
	*output_fd = STDOUT_FILENO;

	if (shell.status && (cmd->logic & IS_AND))
		shell.run = false;
	if (!shell.status && (cmd->logic & IS_OR))
		shell.run = false;

	free_command_chain(cmd);
}
