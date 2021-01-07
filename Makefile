# -*- MakeFile -*-

CC = gcc
SRC = command_node_init.c execute_file.c execute_hshrc.c fork_and_exec.c free_command_chain.c _getenv.c get_executor.c get_history.c _getline.c get_program_path.c get_prompt.c get_tokens.c handle_error.c int_to_str.c make_commands.c _memcpy.c _memset.c prompt_helpers.c _realloc.c save_to_history.c shell.c sigint_handler.c built-ins/alias.c built-ins/cd.c built-ins/env_builtins.c built-ins/exit.c built-ins/help.c built-ins/history.c strings/_strcat.c strings/_strcmp.c strings/_strcpy.c strings/_strdup.c strings/_strlen.c strings/_realloc_string_array.c
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
