#ifndef EXEC_H
# define EXEC_H

# include "../parssing/minishell.h"
# include <sys/wait.h>
# include <fcntl.h>

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

t_cmd	*parse_cmd(s_tokens *tokens);
// void exec_external(t_cmd *c, s_env **env, char **envp);
int		exec_single(t_cmd **c, s_env **env, s_tokens **tokens);
char	**env_list_to_array(s_env *lst);
int		apply_redirs(t_cmd *c);
void	free_strarray(char **arr);

#endif /* EXEC_H */
