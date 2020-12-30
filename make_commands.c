#include "shell.h"

/**
 * make_commands - makes linked list of commands and underlying logic from tokens
 * @tokens: tokens array
 * Return: head of command_t list
 */
command_t *make_commands(char **tokens)
{
	int i, j, arg_index;
	char **args = NULL;
	command_t *head = NULL;
	command_t *tmp = NULL;

	for (i = 0; tokens[i]; i++)
	{
		/*tokens = ["echo", "hello world", ";", "echo", "second"];*/

		/* either tokens[i] is a command -> command_node_nit
		   or tokens[i] its an operator or separator -> switch
		   or its an argument -> add to the command->args = [arg1, arg2, ...]
		*/
		printf("working with: %s\n", tokens[i]);
		switch(tokens[i][0])
		{
			case '>':
			case '<':
				handle_redir(tmp, tokens, &i);
				break;
			case '|':
				handle_pipe(tmp, tokens, &i);
				tmp->args = args;
				args = NULL;;
				break;
			case '&':
				handle_and(tmp, tokens, &i);
				tmp->args = args;
				args = NULL;
				break;
			case ';':
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
					printf("creating new command node!\n");

					/* If a command exists, new command is its ->next */
					if (tmp)
					{
						printf("previous command was %s\n", tmp->command);
						printf("previous tmp->args[0] was %s\n", tmp->args[0]);
						tmp->next = command_node_init(tokens[i]);
						tmp = tmp->next;
						printf("now command is %s\n", tmp->command);
					}
					else	/* first command! */
					{
						printf("first command! Don't come back here!\n");
						head = command_node_init(tokens[i]);
						tmp = head;
					}
				}
				/* Set command to be first token of args array */
				args[arg_index++] = tokens[i];
				printf("new arg added! args[%d] = [%s]\n", arg_index - 1, args[arg_index - 1]);
		}
		printf("\tdone with: %s\n--------\n", tokens[i]);
	}
	return (head);
}