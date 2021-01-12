#include "shell.h"

/**
 * execute_line - makes linked list of commands from tokens
 * @tokens: tokens array
 * Return: cmd of command_t list
 */
void execute_line(char **tokens)
{
	command_t *cmd = NULL;
	int stdin_cpy = dup(STDIN_FILENO), stdout_cpy = dup(STDOUT_FILENO);
	int prev_logic = 0, i;

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
		if (get_IO(cmd, prev_logic) == 1)
		{
			dup2(cmd->input_fd, STDIN_FILENO);
			dup2(cmd->output_fd, STDOUT_FILENO);
			if (cmd->executor) /* execute command */
				shell.status = cmd->executor(cmd->args);
			else
				fork_and_exec(cmd);
			dup2(stdin_cpy, STDIN_FILENO), dup2(stdout_cpy, STDOUT_FILENO);
		}
		prev_logic = cmd->logic;
		if (clean_pipes(cmd) == 0)
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
			cmd->logic |= HAS_EXTRA;
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

/**
 * replace_vars - detects an replaces variables in a shell token
 * @token: token
 * Return: token with all variables replaces
 **/
char *replace_vars(char *token)
{
	char *new_token, *value;
	int i;

	/* check for a '$' . If no dollar signs, return token */
	for (i = 0; token[i] != '$'; i++)
		if (token[i] == '\0')
			return (token);

	if (!token[i + 1] || token[i + 1] == ' ')
		return (token);

	if (_strcmp(token + i, "$$") == 0) /* If '$$' get pid */
		value = int_to_str(shell.pid);
	else if (_strcmp(token + i, "$?") == 0) /* If 'S?' get prev exit status */
		value = int_to_str(shell.status);
	else /* else, get variable value from environment */
		value = _getenv(token + i + 1);
	/* Create token */
	if (value == NULL)
		value = "";
	new_token = _realloc(NULL, i + _strlen(value) + 1);
	sprintf(new_token, "%.*s%s", i, token, value); /* dope-ass printf logic */
	free(token);								   /* free old token */
	if (*value)
		free(value);				  /* free value buffer */
	return (replace_vars(new_token)); /* check for more variables */
}

/**
 * get_IO - formats cmd input and output streams
 * @cmd: command node
 * @prev_logic: previous command's logic
 * Return: 1 on success -1 on failure
 */
int get_IO(command_t *cmd, int prev_logic)
{
	static int pipefds[2];

	if (prev_logic & IS_PIPE) /* get input_fd */
		cmd->input_fd = pipefds[0];
	else
		cmd->input_fd = get_input_fd(cmd);
	if (cmd->input_fd == -1)
		return (-1);

	cmd->output_fd = get_output_fd(cmd); /* get output fd */

	if (cmd->logic & IS_PIPE && !(cmd->logic & (IS_REDIR_OUT | IS_APPEND)))
		pipe(pipefds), cmd->output_fd = pipefds[1];
	if (cmd->output_fd == -1)
		return (-1);
	return (1);
}

/**
 * clean_pipes - clean pipes
 * @cmd: cmd
 * Return: to keep running shell or not
 **/
bool clean_pipes(command_t *cmd)
{
	int logic = cmd->logic, i;

	if (cmd->input_fd > 2)
		close(cmd->input_fd);
	if (cmd->output_fd > 2)
		close(cmd->output_fd);

	free(cmd->path);
	free(cmd->input);
	free(cmd->output);
	if (cmd->args)
		for (i = 0; cmd->args[i]; i++)
			free(cmd->args[i]);
	free(cmd->args);
	free(cmd);

	if (shell.status && (logic & IS_AND))
		return (false);
	if (!shell.status && (logic & IS_OR))
		return (false);

	return (true);
}
