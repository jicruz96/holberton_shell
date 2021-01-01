#include "shell.h"

/**
 * get_tokens - parses file and returns token array, split by spaces
 *
 * @fd: file descriptor of file to parse
 * Return: array of tokens
 **/
char **get_tokens(int fd)
{
	char *line, *token, **tokens, *buf;
	int i;

	/* Get line from file. Save to buf */
	buf = _getline(fd);
	if (buf == NULL)
		return (NULL);
	buf = realloc(buf, 1024);
	line = buf;

	/*  Create array for 256 tokens (strings) */
	tokens = malloc(sizeof(char *) * 256);
	for (i = 0; i < 256; i++)
		tokens[i] = NULL;

	/* Loop as long as parse_line keeps returning tokens */
	for (i = 0; (token = parse_line(&line)); i++)
	{
		/* If a token has an unclosed doublequote, fix it! */
		if (_strcmp(token, "<<") == 0)
		{
			tokens[i++] = token;
			token = get_heredoc(&line, fd);
		}
		else if (*token == '"')
		{
			token = fix_dquote(&line, token, fd);
		}
		tokens[i] = token;
	}

	/* no more tokens? cool. save (or free) buf and return */
	if (shell.interactive)
		save_line_to_history(buf);
	else
		free(buf);
	return (tokens);
}

/**
 * get_heredoc - gets heredoc
 * @line: line to parse
 * @fd: file descriptor (to get more lines if needed)
 * Return: heredoc
 **/
char *get_heredoc(char **line, int fd)
{
	char *token = _strdup(""), *end_tag = parse_line(line), *tmp;
	int token_length = 0, searching_for_end_tag = true;

	while (searching_for_end_tag)
	{
		if (isatty(fd)) /* print PS2 prompt if stdin is terminal */
			dprintf(fd, PS2);

		/* get next line */
		tmp = _getline(fd);

		/* if next line is end tag, clean up and exit loop */
		if (strncmp(tmp, end_tag, _strlen(tmp) - 1) == 0)
		{
			searching_for_end_tag = false;
			free(end_tag);
		}
		else /* else, make space and concat tmp onto token */
		{
			token_length += _strlen(tmp);
			token = realloc(token, token_length + 1);
			_strcat(token, tmp);
		}
		free(tmp);
	}
	return (token);
}

/**
 * fix_dquote - fix double quotes token
 * @line: line to parse
 * @token: token to fix
 * @fd: file descriptor (if more lines are needed)
 * Return: adjusted token
 **/
char *fix_dquote(char **line, char *token, int fd)
{
	int token_length = _strlen(token);
	int j, searching_for_dquote = (token[token_length - 1] != '"');
	char *tmp = NULL;

	while (searching_for_dquote)
	{
		if (shell.interactive) /* print PS2 prompt if stdin is terminal */
			dprintf(fd, PS2);

		/* save next line to end of buf */
		tmp = _getline(fd);
		_strcpy(*line, tmp);
		free(tmp);

		/* search for double quote / increment token_length */
		for (j = 0; (*line)[j] && searching_for_dquote; j++)
		{
			token_length++;
			searching_for_dquote = ((*line)[j] != '"');
		}

		/* make space for extra stuff and concatenate */
		token = realloc(token, token_length + 1);
		_strncat(token, *line, j);

		/* point to end of line */
		*line += j;
	}
	tmp = _strndup(token + 1, token_length - 2);
	free(token);
	return (tmp);
}

/**
 * parse_line - parses a line and returns the next token found
 * @line: pointer to line pointer
 * Return: next token parsed
 **/
char *parse_line(char **line)
{
	char *token, *delims = " \t\n#><&|;\"";
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

	if (!i) /* if no delimiters detected, find end of token */
	{
		if (**line == '"')
			delims = "\"";

		for (i = 1; (*line)[i]; i++)
			for (j = 0; delims[j]; j++)
				if ((*line)[i] == delims[j])
					goto LOOP_EXIT;

		/* adjust i value (for double quote edge case) */
LOOP_EXIT:
		i += (**line == '"' && (*line)[i] == '"');
	}

	token = _strndup(*line, i);
	*line += i;
	return (token);
}
