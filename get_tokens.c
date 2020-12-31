#include "shell.h"

/**
 * get_tokens - parses file and returns token array, split by spaces
 *
 * @fd: file descriptor of file to parse
 * Return: array of tokens
 **/
char **get_tokens(int fd)
{
	char *line, *token, *end_tag, *tmp, **tokens, *home;
	int i, j, token_length, searching_for_dquote, searching_for_end_tag;

	/* Get line from file */
	line = _getline(fd);
	if (line == NULL)
		return (NULL);

	home = line;

	/*  Create array for 256 tokens (strings) */
	tokens = malloc(sizeof(char *) * 256);

	/* Set everything in tokens array to 0 NULL */
	for (i = 0; i < 256; i++)
		tokens[i] = NULL;

	/* Loop as long as parse_line keeps returning tokens */
	for (i = 0; (token = parse_line(&line)); i++)
	{
		/* If a token has an unclosed doublequote, fix it! */
		if (*token == '"' && token[_strlen(token) - 1] != '"')
		{
			/**
			 * we'll need to keep track of the token length, so let's
			 * initialize token_length at the current line length
			 **/
			token_length = _strlen(token);
			searching_for_dquote = true;
			while (searching_for_dquote)
			{
				/* let's get another line */
				/* first, free the current line */
				free(home);
				/* second, print the PS2 prompt if input is a terminal */
				if (isatty(fd))
					dprintf(fd, PS2);
				/* third, get the line */
				line = _getline(fd);
				/* fourth, save reference to line in home variable */
				home = line;
				/* search for double quote / increment token_length */
				for (j = 0; line[j] && searching_for_dquote; j++)
				{
					token_length++;
					/**
					 * if line[j] is '"', this evaluates to false, thus ending
					 * the loop (both this loop and the outer loop).
					 **/
					searching_for_dquote = (line[j] != '"');
				}

				/* make space for extra stuff and concatenate */
				token = realloc(token, token_length + 1);
				_strncat(token, line, j);
			}
			/* When done, set line equal to first character after dquote */
			line = line + j + 1;
		}
		/* If a token is a heredoc, deal with that... */
		else if (strcmp(token, "<<") == 0)
		{
			/* Save heredoc symbol to tokens array and go to index */
			tokens[i++] = token;

			/* next token is heredoc's contents. set to empty string */
			token = _strdup("");
			/* set token length to 0 */
			token_length = 0;

			/* get the end tag */
			end_tag = parse_line(&line);

			tmp = _strdup(line);

			/* about to get a new line, so free reference to previous one */
			free(home);
			searching_for_end_tag = true;
			while (searching_for_end_tag)
			{
				/* first, print the PS2 prompt if input is a terminal */
				if (isatty(fd))
					dprintf(fd, "> ");
				/* second, get the line */
				line = _getline(fd);
				/* check if it's the end tag */
				if (strncmp(line, end_tag, _strlen(line) - 1) == 0)
				{
					/* if it is, clean up and get out of this loop */
					searching_for_end_tag = false;
					free(end_tag);
				}
				else	/* else, make space and concat the line onto token */
				{
					/* add line length to token length */
					token_length += _strlen(line);
					token = realloc(token, token_length + 1);
					_strcat(token, line);
				}
				/* done with line, so free it */
				free(line);
			}
			/* done with heredoc, so reset original line where it left off */
			line = tmp;
			/* set home to tmp as well */
			home = tmp;
		}
		tokens[i] = token;
	}
	/* no more tokens? cool. free home and return */
	free(home);
	return (tokens);
}

/**
 * parse_line - parses a line and returns the next token found
 * @line: pointer to line pointer
 * Return: next token parsed
 **/
char *parse_line(char **line)
{
	char *token, *delims = " \"\t\n#><&|;";
	int i = 0, j = 0;

	if (!line || !(*line))
		return (NULL);
	
	while (**line == ' ' || **line == '\t')
		(*line)++;

	if (!(**line) || **line == '#' || **line == '\n')
		return (NULL);
	
	/* detect delimiters */
	i += (**line == ';');
	i += (**line == '>') * (1 + ((*line)[1] == '>'));
	i += (**line == '<') * (1 + ((*line)[1] == '<'));
	i += (**line == '&') * (1 + ((*line)[1] == '&'));
	i += (**line == '|') * (1 + ((*line)[1] == '|'));
	
	
	if (!i)			/* if no delimiters detected, find end of token */
	{
		if (**line == '"')
			delims = "\"";

		for (i = 1; (*line)[i]; i++)
			for (j = 0; delims[j]; j++)
				if ((*line)[i] == delims[j])
					goto LOOP_EXIT;
		
		/* adjust i value (for double quote edge case) */
		LOOP_EXIT: i += (**line == '"' && (*line)[i] == '"');
	}

	token = _strndup(*line, i);
	*line += i;
	return (token);
}
