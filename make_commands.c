#include "shell.h"

/**
 * make_commands - makes linked list of commands and underlying logic from tokens
 * @tokens: tokens array
 * Return: head of command_t list
 */
command_t *make_commands(char **tokens)
{
	command_t *head = NULL, *tmp = NULL;
	int i, j, arg_index;
	char **args = NULL;

	for (i = 0; tokens[i]; i++)
	{
		switch(tokens[i][0])
		{
			case '>':
			case '<':
				handle_redir(tmp, tokens, &i);
				free(tokens[i - 1]);
				break;
			case '|':
				handle_pipe(tmp, tokens, &i);
				free(tokens[i]);
				tmp->args = args;
				args = NULL;;
				break;
			case '&':
				handle_and(tmp, tokens, &i);
				free(tokens[i]);
				tmp->args = args;
				args = NULL;
				break;
			case ';':
				free(tokens[i]);
				tmp->args = args;
				args = NULL; 
				break;
			default:
			/* If not a separator, save to args array */
				/* if its a fresh new array, allocate memory for it, set index to 0, init new node */
				if (args == NULL)
				{
					/* allocate memory for new args array */
					args = malloc(sizeof(char *) * 256);

					/* init all indexes of args to NULL */
					for (j = 0; args[j]; j++)
						args[j] = NULL;

					/* reset the index counter to 0 */
					arg_index = 0;

					/* If a command exists, new command is its ->next */
					if (tmp)
					{
						tmp->next = command_node_init(tokens[i]);
						tmp = tmp->next;
					}
					else	/* first command! */
					{
						head = command_node_init(tokens[i]);
						tmp = head;
					}
				}
				/* Add token to args array */
				args[arg_index++] = tokens[i];
		}
	}

	tmp->args = args;
	return (head);
}
