CC = cc
LIBFT = libft/libft.a
LIBS = -lreadline -lcurses
SRCS = parssing/minishell.c parssing/Utils/linked_env.c parssing/Utils/tokens.c parssing/Utils/linked_tokens.c exec/exec.c exec/parsing_cmds.c exec/env_list_to_array.c builtins/builtins.c builtins/echo.c
HEADER = include/minishell.h libft/libft.h
FLAGS = -fsanitize=address -Wall -Wextra -Werror -g
OBJS = $(SRCS:.c=.o)
NAME = Minishell

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C libft fclean all

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(FLAGS) $(LIBFT) $(LIBS) -o $(NAME)

.c.o: $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean 

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: clean fclean re all
