#include "shell.h"

/**
 * make_commands - makes linked list of commands from tokens
 * @tokens: tokens array
 * Return: head of command_t list
 */
command_t *make_commands(char **tokens)
{
	command_t *head = NULL, *cmd = NULL, *prev = NULL;
	int i, j, k;

	for (i = 0; tokens[i]; prev = cmd, free(tokens[j]), i++)
	{
		cmd = command_node_init(tokens[i++]);
		if (prev)
			prev->next = cmd;
		else
			head = cmd;

		for (j = i; tokens[j] && cmd->logic == 0;)
			if (tokens[j][0] == '|')
				cmd->logic |= (tokens[j][1] == '|') ? IS_OR : IS_PIPE;
			else if (_strcmp(tokens[j], "&&") == 0)
				cmd->logic |= IS_AND;
			else if (tokens[j][0] != ';')
				j++;
			else
				break;

		for (k = 1; i < j; i++)
			if (tokens[i][0] == '<')
			{
				cmd->logic |= (tokens[i][1] == '<') ? IS_HEREDOC : IS_REDIR_IN;
				free(tokens[i++]), cmd->input = tokens[i];
			}
			else if (tokens[i][0] == '>')
			{
				cmd->logic |= (tokens[i][1] == '>') ? IS_APPEND : IS_REDIR_OUT;
				free(tokens[i++]), cmd->output = tokens[i];
			}
			else
			{
				cmd->args[k++] = tokens[i];
			}
	}
	return (head);
}
