#include "shell.h"

/**
 * fork_and_exec - wrapper for pipes vs non pipes 
 * @command: command node
 * Return: status
 */
int fork_and_exec(command_t *command)
{
	pid_t child_pid;
	int status = 0;
	int stdin_cpy = dup(STDIN_FILENO);
	int stdout_cpy = dup(STDOUT_FILENO);
	int input_fd = STDIN_FILENO;
	int output_fd = STDOUT_FILENO;
	int fd;
	int pipefds[2];
	int perms;
	int i;
	command_t *tmp;

	for (tmp = command; tmp; tmp = tmp->next)
	{
		/* Get input_fd if is_redir_in */
		if (tmp->input)
		{
			/* try to open input */
			fd = open(tmp->input, O_RDONLY);
			/* if file doesn't exist, go to end */
			if (fd == -1)
			{
				status = handle_error(errno);
				goto END;
			}

			/* if input is stdin, set input to this file instead */
			if (input_fd == STDIN_FILENO)
			{
				input_fd = fd;
			}
			/* if input is not stdin, it's a pipe from a previous cmd */
			else
			{
				/* this will require its own logic but i'll come back to it */
				input_fd = fd;
			}
		}
		
		/* Get input_fd if is_heredoc */
		if ((tmp->logic & IS_HEREDOC) && !tmp->args[1])
		{
			/* make pipe for heredoc */
			if (pipe(pipefds) == -1)
			{
				status = handle_error(errno);
				goto END;
			}

			/* write contents onto pipe */
			write(pipefds[1], tmp->heredoc, _strlen(tmp->args[i]));

			/* close writing side of pipe */
			close(pipefds[1]);

			/* set input to reading side of pipe */
			input_fd = pipefds[0];
		}

		/* Get output_fd is is_redir_out or is_redir_append */
		if (tmp->output)
		{
			perms = O_CREAT | O_RDWR;
			if (tmp->logic == IS_APPEND)
				perms |= O_APPEND;
			else
				perms |= O_TRUNC;
			output_fd = open(tmp->output, perms);
			if (output_fd == -1)
			{
				status = handle_error(errno);
				goto END;
			}
		}

		/* Get output_fd if is_pipe_writer */	
		if (tmp->logic & IS_PIPE_WRITER)
		{
			if (pipe(pipefds) == -1)
			{
				status = handle_error(errno);
				goto END;
			}
			output_fd = pipefds[1];
		}
		
		if (dup2(input_fd, STDIN_FILENO) == -1)	/* dup2 should never fail but just in case */
		{
			status = handle_error(errno);
			goto END;
		}
		if (dup2(output_fd, STDOUT_FILENO) == -1)	/* dup2 should never fail but just in case */
		{
			status = handle_error(errno)
			goto END;
		}

		/* Fork */
		child_pid = fork();

		/* Child executes */
		if (child_pid == 0)
		{
			tmp->executor(tmp->path, tmp->args));
			return (handle_error(errno));
		}
		
		/* Parent waits (or detects forking error) */
		if (child_pid == -1 || waitpid(child_pid, &status, 0) == -1)
			status = handle_error(errno);
		else
			status = WEXITSTATUS(status);
		
		END:

		/* Reset stdin and stdout */
		dup2(stdin_cpy, STDIN_FILENO);
		dup2(stdout_cpy, STDOUT_FILENO);

		/* Close and reset input_fd and output_fd */
		if (input_fd > 2)
			close(input_fd);
		if (tmp->logic & IS_PIPE_WRITER)
			input_fd = pipefds[0];
		else
			input_fd = STDIN_FILENO;
		if (output_fd > 2)
			close(output_fd);
		output_fd = STDOUT_FILENO;

		/* Check command logic to see if we continue executing */
		if (status && (tmp->logic & AND_OP))
			break;
		if (!status && (tmp->logic & OR_OP))
			break; 
		if (shell.run == false)
			break;
	}

	return (status);

}

/**
 * handle_error - prints error messages
 * @code: error code
 * Return error code
 **/
int handle_error(int code)
{
	perror("hsh");
	return (code);
}

/**
 * execute_command - wrapper for execve
 * @path: path
 * @args: args
 * Return: status
 **/
int execute_command(char *path, char **args)
{
	return (execve(path, args, environ));
}
