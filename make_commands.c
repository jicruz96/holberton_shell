#include "shell.h"

/**
 * execute_line - makes linked list of commands from tokens
 * @tokens: tokens array
 * Return: head of command_t list
 */
void execute_line(char **tokens)
{
	command_t *cmd = NULL;
	int stdin_cpy = dup(STDIN_FILENO), stdout_cpy = dup(STDOUT_FILENO);
	int input_fd = -1, output_fd = -1, prev_logic = 0, pipefds[2], i;

	/* Loop through all tokens while shell is running */
	for (i = 0; tokens[i] && shell.run; i++)
	{
		/* MAKE COMMAND */
		if (IS_SEPARATOR(tokens[i]) || IS_REDIR_TOKEN(tokens[i]))
		{
			shell.status = handle_syntax_error(tokens[i--]);
			break;
		}
		cmd = make_command(tokens, &i);

		if (prev_logic & IS_PIPE) /* get input_fd */
			input_fd = pipefds[0];
		else
			input_fd = get_input_fd(cmd);
		if (input_fd == -1)
			goto END;
		output_fd = get_output_fd(cmd); /* get output fd */
		if (output_fd == -1)
			goto END;
		if ((cmd->logic & IS_PIPE) && !(cmd->logic & (IS_REDIR_OUT | IS_APPEND)))
			pipe(pipefds), output_fd = pipefds[1];
		dup2(input_fd, STDIN_FILENO), dup2(output_fd, STDOUT_FILENO);
		if (cmd->executor) /* execute command */
			shell.status = cmd->executor(cmd->args);
		else
			fork_and_exec(cmd);
		dup2(stdin_cpy, STDIN_FILENO), dup2(stdout_cpy, STDOUT_FILENO);
END:
		prev_logic = cmd->logic;
		if (!clean_pipes(cmd, &input_fd, &output_fd))
			break;
	}
	while (tokens[++i])
		free(tokens[i]);
}

/**
 * make_command - makes a single command
 * @tokens: array of arguments
 * @i: index of token array we left off at
 * Return: command to execute
 */
command_t *make_command(char **tokens, int *i)
{
	int j;
	command_t *cmd = command_node_init(replace_vars(tokens[(*i)++]));

	/* COMMAND READING LOOP (ENDS WHEN THE COMMANDS ENDS*/
	for (j = 1; !IS_SEPARATOR(tokens[*i]); (*i)++)
	{
		/* Detect file redirectors */
		if (tokens[*i][0] == '<')
		{
			cmd->logic |= (tokens[*i][1] == '<') ? IS_HEREDOC : IS_REDIR_IN;
			free(tokens[(*i)++]), cmd->input = replace_vars(tokens[*i]);
		}
		else if (tokens[*i][0] == '>')
		{
			cmd->logic |= (tokens[*i][0] == '>') ? IS_APPEND : IS_REDIR_OUT;
			free(tokens[(*i)++]), cmd->output = replace_vars(tokens[*i]);
		}
		else if (IS_NUMERIC(tokens[*i][0]) && tokens[*i][1] == '>')
		{
			cmd->logic |= HAS_EXTRA, cmd->extra_fd = tokens[*i][0] + '0';
			free(tokens[(*i)++]), cmd->output = replace_vars(tokens[*i]);
		}
		else /* if not a redirect, save to argument array */
		{
			cmd->args[j++] = replace_vars(tokens[*i]);
		}
	}

	/* COMMAND SEPARATOR LOGIC */
	if (tokens[*i])
	{
		if (tokens[*i][0] == '|')
			cmd->logic |= (tokens[*i][1] == '|') ? IS_OR : IS_PIPE;
		else if (_strcmp(tokens[*i], "&&") == 0)
			cmd->logic |= IS_AND;
		free(tokens[(*i)]);
	}

	return (cmd);
}
