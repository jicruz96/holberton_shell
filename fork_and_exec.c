#include "shell.h"

/**
 * execute_commands - wrapper for pipes vs non pipes
 * @command: command node
 * Return: status
 */
int execute_commands(command_t *command)
{
	int stdin_cpy = dup(STDIN_FILENO), stdout_cpy = dup(STDOUT_FILENO);
	int input_fd = STDIN_FILENO, output_fd, pipefds[2];
	command_t *tmp;

	for (tmp = command; tmp && shell.run; tmp = tmp->next)
	{
		/* Get input and output */
		if (input_fd == STDIN_FILENO)
			input_fd = get_input_fd(tmp);
		output_fd = get_output_fd(tmp);

		/* If pipe, create pipe, set output to pipe writer */
		if (tmp->logic & IS_PIPE)
			pipe(pipefds), output_fd = pipefds[1];

		/* Redirect stdin and stdout to the input and output */
		dup2(input_fd, STDIN_FILENO), dup2(output_fd, STDOUT_FILENO);
		if (tmp->executor)
			shell.status = tmp->executor(tmp->args);
		else
			fork_and_exec(tmp);

		/* Redirect input and output to stdin and stdout */
		dup2(stdin_cpy, STDIN_FILENO), dup2(stdout_cpy, STDOUT_FILENO);

		/* Clean pipes and GTFO if needed */
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
	return (true);
}
