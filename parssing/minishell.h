/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:18:42 by amsbai            #+#    #+#             */
/*   Updated: 2025/05/13 14:04:30 by amsbai           ###   ########.fr       */
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
// # include "../builtins/builtins.h"
# include <readline/readline.h>
# include <readline/history.h>

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

typedef struct f_env {
	char	*data;
	char	*value;
	void	*tmp;
	struct f_env	*next;
}	s_env ; // this is the strcut where the enviroment variables are stored

typedef struct s_redir
{
    int		type;       /* R_IN, R_OUT, etc. */
    char	*filename;   /* target file or heredoc limiter */
    int		fd;         /* fd to dup to (0=stdin,1=stdout) */
} t_redir;

typedef struct s_cmd
{
    char    **argv;      /* NULL-terminated argument array */
    t_redir *redir;      /* array of redirections */
    int      n_redir;    /* number of redirections */
    int      builtin_id; /* index in dispatch table or -1 */
    struct s_cmd *next;  /* next command in pipeline */
} t_cmd;

typedef struct f_tokens {
	enum t_sign type;
	char	*value;
	struct f_tokens	*next;
}	s_tokens ; //this struct is used to tokenize the command elements

int			main(int ac, char **av, char **env);
void		free_cmd(t_cmd **cmd);
char		**count_malloc(char const *str);
char		**ft_split(char const *s, char c);
void		free_cmd(t_cmd **cmd);
void		*ft_realloc(void *str, size_t newsize);
int			exec_single(t_cmd **c, s_env **env, s_tokens **tokens);
void		tokenize_shell(char* input, s_tokens **cmd, s_env **listed);
int			ft_strcmp(const char *s1, const char *s2);
char		*substr_quotes(char const *s, unsigned int start, size_t len, size_t i);
int			exec_pipeline(t_cmd *first, s_env **env, s_tokens **);
t_cmd		*parse_cmd(s_tokens *tokens);
int			get_heredoc_fd(const char *limiter);
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