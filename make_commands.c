#include "shell.h"
/**
 * make_commands - makes linked list of commands and underlying logic from tokens
 * @tokens: tokens array
 * Return: head of command_t list
 */
command_t *make_commands(char *tokens)
{
	/* command_t *head;
	int i;
	prev_command = NULL
	for (i = 0; args[i]; i++)

		path = get_command_path(args[i]);
		if path == NULL:
			if path is built-in:
				command->logic = IS_BUILTIN;
			else:
				error()
		new_node = command_node_init(command, args[i])
		if prev:
			prev->next = new_node
		new_node->prev = prev
		i += 1
		if args[i] == NULL:
			break*/
	   
		
		/* Getting it if it anything else: operators, redirects, pipes, separators, argument*/
		/*flag = True
		j = 0
		i = 0
		while args[i]:
			if args[i] is a redirect:
				command->logic = IS_REDIRECT
				if '<' then:
					command->input_name = args[i + 1]
				else if '>':
					command->output_name = args[i + 1]
				else if '>>':
					command->output_name = args[i + 1]
					command->logic = IS_APPEND
				i += 2
			else if args[i] is heredoc ('<<'):
				command->logic = IS_HEREDOC
				command->input = make_heredoc(args, &i)
				break
			else if args[i] is a pipe ('||'):
				command->logic = IS_PIPE_WRITER
				i += 1
				break
			else if args[i] is a operators ('&&', '||'):
				command->logic = either AND or OR depending on whats args[i] is
			else:
				command->args[j] = args[i]
				j += 1
				i += 1

		prev_command = new_node*/

	return head*/
	return (head);
}
