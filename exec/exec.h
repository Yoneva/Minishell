#ifndef EXEC_H
# define EXEC_H

# include "../parssing/minishell.h"

/* Builtin identifiers */
enum e_builtin {
    B_ECHO,
    B_CD,
    B_PWD,
    B_EXPORT,
    B_UNSET,
    B_ENV,
    B_EXIT
};

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

/* Builtin function pointer */
typedef int (*t_builtin_fn)(t_cmd *cmd, s_env **env);

/* Dispatch table for builtins */
typedef struct s_bdispatch {
    char          *name;
    t_builtin_fn   fn;
}   t_bdispatch;

/* External declaration of the builtin dispatch table */
extern const t_bdispatch  g_builtins[];

t_cmd *parse_cmd(s_tokens *tokens);
int exec_single(t_cmd *c, s_env **env);
char	**env_list_to_array(s_env *lst);
void	free_strarray(char **arr);
int ft_strcmp(const char *s1, const char *s2);
#endif /* EXEC_H */
