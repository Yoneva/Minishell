CC = cc
LIBFT = libft/libft.a
LIBS = -lreadline -lcurses
SRCS = parssing/minishell.c parssing/Utils/linked_env.c parssing/Utils/tokens.c parssing/Utils/linked_tokens.c \
		exec/exec.c parssing/Utils/parsing_cmds.c exec/env_list_to_array.c exec/redirs_utils.c builtins/builtins.c \
		builtins/echo.c builtins/pwd.c builtins/env.c builtins/exit.c builtins/cleanup.c builtins/unset.c \
		builtins/export.c builtins/cd.c builtins/env_helpers.c parssing/Utils/substrmodified.c \
		parssing/Utils/ft_strcmp.c exec/exec_pipeline.c exec/heredoc.c parssing/Utils/helper_file.c \
		parssing/Utils/replace_var.c parssing/Utils/helper_file2.c parssing/Utils/redirections.c \
		parssing/Utils/tokens_helper.c
HEADER = parssing/minishell.h libft/libft.h exec/exec.h builtins/builtins.h
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