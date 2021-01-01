#include "shell.h"

/**
 * fork_and_exec - wrapper for pipes vs non pipes
 * @command: command node
 * Return: status
 */
int fork_and_exec(command_t *command)
{
	pid_t child_pid;
	int stdin_cpy = dup(STDIN_FILENO), stdout_cpy = dup(STDOUT_FILENO);
	int input_fd = STDIN_FILENO, output_fd, pipefds[2], status = 0;
	command_t *tmp;

	for (tmp = command; tmp && shell.run; tmp = tmp->next)
	{
		if (input_fd == STDIN_FILENO)
			input_fd = get_input_fd(tmp);
		output_fd = get_output_fd(tmp);
		if (tmp->logic & IS_PIPE)
			pipe(pipefds), output_fd = pipefds[1];
		dup2(input_fd, STDIN_FILENO), dup2(output_fd, STDOUT_FILENO);
		child_pid = fork();
		if (child_pid == 0) /* child executes */
		{
			if (tmp->executor)
				shell.status = tmp->executor(tmp->args);
			else
				shell.status = execve(tmp->path, tmp->args, environ);
			if (shell.run && shell.status)
				exit(handle_error(errno));
			exit(shell.status);
		}
		/* Parent waits (or detects forking error) */
		if (child_pid == -1 || waitpid(child_pid, &status, 0) == -1)
			shell.status = handle_error(errno);
		else
			shell.status = WEXITSTATUS(status);
		dup2(stdin_cpy, STDIN_FILENO), dup2(stdout_cpy, STDOUT_FILENO);
		if (clean_pipes(tmp, &input_fd, &output_fd) == false)
		{
			if (tmp->logic & IS_PIPE)
				close(pipefds[0]);
			break;
		}
		if (tmp->logic & IS_PIPE)
			input_fd = pipefds[0];
	}
	return (shell.status);
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
 * Return: true or false
 **/
int clean_pipes(command_t *cmd, int *input_fd, int *output_fd)
{

	if (*input_fd > 2)
		close(*input_fd);
	if (*output_fd > 2)
		close(*output_fd);

	*input_fd = STDIN_FILENO;
	*output_fd = STDOUT_FILENO;

	if (shell.status && (cmd->logic & IS_AND))
		return (false);
	if (!shell.status && (cmd->logic & IS_OR))
		return (false);
	if (_strcmp(cmd->command, "exit") == 0)
	{
		shell.run = false;
		return (false);
	}
	return (true);
}

/**
 * handle_error - prints error messages
 * @code: error code
 * Return: error code
 **/
int handle_error(int code)
{
	char error_msg[256];

	sprintf(error_msg, "%s: %d", shell.name, shell.lines);
	perror(error_msg);
	return (code);
}
