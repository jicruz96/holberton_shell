#include "../shell.h"
/**
 * handle_redir - function that handles logic
 * if passed in token is a riderect '>' '<'
 * @command: node that represents the command
 * @tokens: array of tokens
 * @i: place in our tokens array
 * Return: void
 */
void handle_redir(command_t *command, char **tokens, int *i)
{
	if (tokens[*i][0] == '<') /* It's a '<' */
	{
		if (tokens[*i][1] == '<') /* it's a heredoc */
		{
			command->logic |= IS_HEREDOC;
			/* tokens[i + 1] should equal the entire heredoc text */
			*i += 1;
			command->heredoc = tokens[*i];
		}
		else /* it's an input redirect! */
		{
			command->logic |= IS_REDIR_IN;
			*i += 1;
            command->input = tokens[*i];
		}
	}
	else /* It's a '>' */
	{
		if (tokens[*i][1] == '>') /* It's an append redirect */
            command->logic |= IS_APPEND;
		else	/* it's an overwrite redirect */
            command->logic |= IS_REDIR_OUT;
		*i += 1;
		command->output = tokens[*i];
	}
}

/**
 * handle_pipe - function that handles logic
 * if passed in token is a riderect '|' '||'
 * @command: node that represents the command
 * @tokens: array of tokens
 * @i: place in our tokens array
 * Return: void
 */
void handle_pipe(command_t *command, char **tokens, int *i)
{
	if (tokens[*i][1] == '|') /* This is an OR */
        command->logic |= IS_OR;
    else
        command->logic |= IS_PIPE;
}
/**
 * handle_and - function that handles logic
 * if passed in token is a redir '&' "&&"
 * @command: node that represents the command
 * @tokens: array of tokens
 * @i: place in our tokens array
 * Return: void
 */
void handle_and(command_t *command, char **tokens, int *i)
{
    if (tokens[*i][1] == '&' && tokens[*i][2] == '\0')
        command->logic |= IS_AND;
}