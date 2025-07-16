CC = cc
LIBFT = libft/libft.a
LIBS = -lreadline -lcurses
SRCS = parssing/minishell.c parssing/Utils/linked_env.c parssing/Utils/tokens.c parssing/Utils/linked_tokens.c \
		exec/exec.c parssing/Utils/parsing_cmds.c exec/env_list_to_array.c exec/redirs_utils.c builtins/builtins.c \
		builtins/echo.c builtins/pwd.c builtins/env.c builtins/exit.c builtins/cleanup.c builtins/unset.c \
		builtins/export.c builtins/cd.c builtins/env_helpers.c parssing/Utils/substrmodified.c \
		parssing/Utils/ft_strcmp.c exec/exec_pipeline.c exec/heredoc.c parssing/Utils/helper_file.c \
		parssing/Utils/replace_var.c parssing/Utils/helper_file2.c parssing/Utils/redirections.c \
		parssing/Utils/tokens_helper.c parssing/Utils/variables.c exec/pipe_utils.c builtins/status.c
HEADER = parssing/minishell.h libft/libft.h exec/exec.h builtins/builtins.h builtins/status.h
FLAGS = -fsanitize=address -Wall -Wextra -Werror -g 
OBJS = $(SRCS:.c=.o)
NAME = Minishell


all: banner $(LIBFT) $(NAME) finish

banner:
	@echo "\033[1;35m"
	@echo " __  __ _       _     _          _ _ "
	@echo "|  \/  (_)     (_)   | |        | | |"
	@echo "| \  / |_ _ __  _ ___| |__   ___| | |"
	@echo "| |\/| | | '_ \| / __| '_ \ / _ \ | |"
	@echo "| |  | | | | | | \__ \ | | |  __/ | |"
	@echo "|_|  |_|_|_| |_|_|___/_| |_|\___|_|_|"
	@echo ""
	@echo "          Minishell compiling..."
	@echo "\033[0m"

finish:
	@echo "\033[1;32m✔️ Minishell Compiled\033[0m"

# Modified all target to include banner and finish

$(LIBFT):
	@$(MAKE) -C libft

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(FLAGS) $(LIBFT) $(LIBS) -o $(NAME)

.c.o: $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C libft clean 
	@echo "Cleaned :3"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: clean fclean re all