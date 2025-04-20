/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimaneyousr <aimaneyousr@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:18:42 by amsbai            #+#    #+#             */
/*   Updated: 2025/04/20 16:06:45 by aimaneyousr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define MAX_TOKENS 100
#define MAX_TOKEN_SIZE 256

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_node {
	void *str;
	struct s_node *next;
} t_node ; //generic linked list

typedef struct f_env {
	char	*data;
	char	*value;
	struct f_env	*next;
}	s_env ; // this is the strcut where the enviroment variables are stored

enum t_sign {
	N_PIPE,
	N_DOUBLE_QUOTE,
	N_SINGLE_QUOTE,
	N_AND_SIGN,
	N_OR_SIGN,
	N_WORD,
	N_INPUT_SIGN,
	N_OUTPUT_SIGN,
	N_APPEND_SIGN,
	N_HEREDOC_SIGN,
};

typedef struct f_tokens {
	enum t_sign type;
	char	*value;
	int		len;
	struct f_tokens	*next;
}	s_tokens ; //this struct is used to tokenize the command elements

char	**count_malloc(char const *str);
char	**ft_slit(char const *s, char c);
t_node	*f_lstlast(t_node *lst);
void	f_lstadd_back(t_node **lst, t_node *new);
t_node	*f_lstnew(void);
void	*ft_realloc(void *str, size_t newsize);
void	tokenize_shell(const char* input, char **tokens, s_tokens *cmd);

#endif