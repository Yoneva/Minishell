CC = cc
LIBFT = libft/libft.a
LIBS = -lreadline -lcurses
SRCS = parssing/minishell.c parssing/Utils/linked_env.c parssing/Utils/tokens.c parssing/Utils/linked_tokens.c \
		exec/exec.c exec/parsing_cmds.c exec/env_list_to_array.c exec/redirs_utils.c builtins/builtins.c \
		builtins/echo.c builtins/pwd.c builtins/env.c builtins/exit.c builtins/cleanup.c builtins/unset.c \
		builtins/export.c builtins/cd.c builtins/env_helpers.c parssing/Utils/substrmodified.c
HEADER = parssing/minishell.h libft/libft.h exec/exec.h builtins/builtins.h exec/exec.h
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
