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
	int pipefds[2];
	int perms;
	command_t *tmp;

	for (tmp = command; tmp; tmp = tmp->next)
	{
		/* Get input_fd if is_redir_in */
		if (tmp->logic & IS_REDIR_IN)
		{
			/* try to open input */
			input_fd = open(tmp->input, O_RDONLY);
			/* if file doesn't exist, go to end */
			if (input_fd == -1)
			{
				shell.status = handle_error(errno);
				goto END;
			}
		}
		
		/* Get input_fd if is_heredoc */
		if ((tmp->logic & IS_HEREDOC) && tmp->args[1] == NULL)
		{
			/* make pipe for heredoc */
			if (pipe(pipefds) == -1)
			{
				shell.status = handle_error(errno);
				goto END;
			}

			/* write contents onto pipe */
			write(pipefds[1], tmp->input, _strlen(tmp->input));

			/* close writing side of pipe */
			close(pipefds[1]);

			/* set input to reading side of pipe */
			input_fd = pipefds[0];
		}

		/* Get output_fd is is_redir_out or is_redir_append */
		if (tmp->output)
		{
			perms = O_CREAT | O_RDWR;
			if (tmp->logic & IS_APPEND)
				perms |= O_APPEND;
			else
				perms |= O_TRUNC;
			output_fd = open(tmp->output, perms, 0644);
			if (output_fd == -1)
			{
				shell.status = handle_error(errno);
				goto END;
			}
		}

		/* Get output_fd if is_pipe */	
		if (tmp->logic & IS_PIPE)
		{
			if (pipe(pipefds) == -1)
			{
				shell.status = handle_error(errno);
				goto END;
			}
			output_fd = pipefds[1];
		}
		

		if (dup2(input_fd, STDIN_FILENO) == -1)	/* dup2 should never fail but just in case */
		{
			shell.status = handle_error(errno);
			goto END;
		}
		if (dup2(output_fd, STDOUT_FILENO) == -1)	/* dup2 should never fail but just in case */
		{
			shell.status = handle_error(errno);
			goto END;
		}

		/* Fork */
		child_pid = fork();

		/* Child executes */
		if (child_pid == 0)
		{
			if (tmp->executor)
				shell.status = tmp->executor(tmp->args);
			else
				shell.status = execve(tmp->path, tmp->args, environ);
			if (shell.run && shell.status)
				return (handle_error(errno));
			return (shell.status);
		}
		
		/* Parent waits (or detects forking error) */
		if (child_pid == -1 || waitpid(child_pid, &status, 0) == -1)
			shell.status = handle_error(errno);
		else
			shell.status = WEXITSTATUS(status);
		
		END:

		/* Reset stdin and stdout */
		dup2(stdin_cpy, STDIN_FILENO);
		dup2(stdout_cpy, STDOUT_FILENO);

		/* Close and reset input_fd and output_fd */
		if (input_fd > 2)
			close(input_fd);
		if (tmp->logic & IS_PIPE)
			input_fd = pipefds[0];
		else
			input_fd = STDIN_FILENO;
		if (output_fd > 2)
			close(output_fd);
		output_fd = STDOUT_FILENO;

		/* Check command logic to see if we continue executing */
		if (shell.status && (tmp->logic & IS_AND))
			break;
		if (!shell.status && (tmp->logic & IS_OR))
			break; 
		if (shell.run == false)
			break;
	}

	return (shell.status);

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
int execute_command(char **args)
{
	printf("we are executing %s\n", args[0]);
	return (execve(args[0], args, environ));
}
