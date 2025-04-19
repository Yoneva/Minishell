CC = cc
FLAGS = -Wall -Wextra -Werror -g
HEADER = minishell.h ../libft/libft.h
SRCS = minishell.c Utils/linked.c Utils/ft_realloc.c Utils/count_words.c  Utils/tokens.c
OBJS = $(SRCS:.c=.o)
NAME = Minishell
LIBFT = /Users/amsbai/Desktop/minishell/libft/libft.a
LIBS = -lreadline -lcurses

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

.c.o: $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
