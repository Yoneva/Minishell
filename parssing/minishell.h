/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:18:42 by amsbai            #+#    #+#             */
/*   Updated: 2025/07/11 15:23:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_status;

enum e_sign
{
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

typedef struct f_env
{
	char			*data;
	char			*value;
	struct f_env	*next;
}	t_env;

typedef struct t_redir
{
	int		type;
	char	*filename;
	int		fd;
}	t_redir;

typedef struct t_cmd
{
	char			**argv;
	t_redir			*redir;
	int				n_redir;
	int				builtin_id;
	struct t_cmd	*next;
}	t_cmd;

typedef struct f_tokens
{
	enum e_sign		type;
	char			*value;
	struct f_tokens	*next;
}	t_tokens;

typedef struct s_token_context
{
	t_tokens	**cmd;
	t_env		**listed;
	int			has_word;
}	t_token_context;

int			main(int ac, char **av, char **env);
int			skip_spaces(const char *str, int i);
char		**ft_split(char const *s, char c);
int			exec_single(t_cmd **c, t_env **env);
int			if_envariable(char *str, char **word, t_env **env);
void		tokenize_shell(char *input, t_tokens **cmd, t_env **listed);
int			ft_strcmp(const char *s1, const char *s2);
char		*substr_quotes(char const *s, unsigned int start,
				size_t len, size_t i);
int			exec_pipeline(t_cmd *first, t_env **env);
int			get_heredoc_fd(const char *limiter);
void		*ft_realloc(void *str, size_t newsize);
char		*ft_itoa(int nbr);
char		*replace_in_double(int i, int j, char *input, t_env **env);
int			process_word(char *input, int i, t_tokens **cmd, t_env **listed);
int			first_case(t_tokens **node, char *input, t_tokens **cmd,
				int *has_word);
int			process_token(char *input, int i, t_token_context *ctx);
int			find_equale(char *str);

// for cmd struct
t_cmd		*parse_cmd(t_tokens *tokens);
void		free_cmd(t_cmd **cmd);

// for env struct
t_env		*ft_envlast(t_env *lst);
void		ft_envadd_back(t_env **lst, t_env *new_node);
t_env		*ft_envnew(void);
void		ft_envclear(t_env **lst);
void		fill_env_list(char **env, t_env **list);
void		*serachforvar(char *input, t_env **env);

// for tokens struct
t_tokens	*ft_tokenlast(t_tokens *lst);
void		ft_tokenadd_back(t_tokens **lst, t_tokens *new_node);
t_tokens	*ft_tokenew(void);
void		ft_tokensclear(t_tokens **lst);
int			single_quote(char *str, char **h, char **tmp);
int			double_quote(char *str, char **word, char **tmp, t_env **h);
int			pipes(const char *str, int i, t_tokens **cmd);
int			redirections1(const char *str, int i, t_tokens **cmd);
int			redirections2(const char *str, int i, t_tokens **cmd);

#endif