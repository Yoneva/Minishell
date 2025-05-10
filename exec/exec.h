#ifndef EXEC_H
# define EXEC_H

# include "../parssing/minishell.h"

/* Single redirection descriptor */
typedef struct s_redir
{
    int		type;       /* R_IN, R_OUT, etc. */
    char	*filename;   /* target file or heredoc limiter */
    int		fd;         /* fd to dup to (0=stdin,1=stdout) */
} t_redir;

/* Command node for execution */
typedef struct s_cmd
{
    char    **argv;      /* NULL-terminated argument array */
    t_redir *redir;      /* array of redirections */
    int      n_redir;    /* number of redirections */
    int      builtin_id; /* index in dispatch table or -1 */
    struct s_cmd *next;  /* next command in pipeline */
} t_cmd;

extern int	g_status;

t_cmd *parse_cmd(s_tokens *tokens);
// void exec_external(t_cmd *c, s_env **env, char **envp);
void exec_external(t_cmd *c, s_env **env, char **envp);
int exec_single(t_cmd *c, s_env **env);
char	**env_list_to_array(s_env *lst);
int	apply_redirs(t_cmd *c);
int	pipe_count(t_cmd *c);
int	open_all_pipes(int n, int p[][2]);
void	close_all_pipes(int n, int p[][2]);
int	 exec_pipeline(t_cmd *first, s_env **env);
void	free_strarray(char **arr);
int ft_strcmp(const char *s1, const char *s2);
int     get_heredoc_fd(const char *limiter);
#endif /* EXEC_H */
