/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:18:42 by amsbai            #+#    #+#             */
/*   Updated: 2025/05/08 18:35:15 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include "../libft/libft.h"
// # include "../exec/exec.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct f_env {
	char	*data;
	char	*value;
	void	*tmp;
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
	struct f_tokens	*next;
}	s_tokens ; //this struct is used to tokenize the command elements

// int			main(int ac, char **av, char **env);
char		**count_malloc(char const *str);
char		**ft_split(char const *s, char c);
void		*ft_realloc(void *str, size_t newsize);
void		tokenize_shell(char* input, s_tokens **cmd, s_env **listed);
int			ft_strcmp(const char *s1, const char *s2);
char		*substr_quotes(char const *s, unsigned int start, size_t len, size_t i);
// for env struct
s_env		*ft_envlast(s_env *lst);
void		ft_envadd_back(s_env **lst, s_env *new_node);
s_env		*ft_envnew(void);
void		ft_envclear(s_env **lst);
// for tokens struct
s_tokens	*ft_tokenlast(s_tokens *lst);
void		ft_tokenadd_back(s_tokens **lst, s_tokens *new_node);
s_tokens	*ft_tokenew(void);
void		ft_tokensclear(s_tokens **lst);

void	fill_env_list(char **env, s_env **list);

#endif