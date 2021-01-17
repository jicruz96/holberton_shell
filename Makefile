# -*- MakeFile -*-

CC = gcc
SRC = 0-main.c 1-get_tokens.c 2-command_config.c 3-get_IO.c 4-execute.c helpers/_getenv.c helpers/_getline.c helpers/handle_error.c helpers/prompt_helpers.c helpers/get_prompt.c helpers/_realloc.c built-ins/alias.c built-ins/cd.c built-ins/env.c built-ins/setenv.c built-ins/unsetenv.c built-ins/exit.c built-ins/history.c built-ins/help.c strings/_strcat.c strings/_strcmp.c strings/_strcpy.c strings/_strdup.c strings/_strlen.c strings/_puts.c strings/_realloc_string_array.c
OBJ = $(SRC:.c=.o)
NAME = hsh
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -pedantic -g

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

fclean: oclean clean

oclean:
	$(RM) $(OBJ)

clean:
	$(RM) *~ $(NAME)

re: oclean all
