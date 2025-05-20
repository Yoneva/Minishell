#ifndef BUILTINS_H
# define BUILTINS_H

# include "../parssing/minishell.h"
# include "../exec/exec.h"


/* Builtin function pointer */
typedef int (*t_builtin_fn)(t_cmd *cmd, s_env **env);

/* Dispatch table for builtins */
typedef struct s_bdispatch {
    char          *name;
    t_builtin_fn   fn;
}   t_bdispatch;

/* External declaration of the builtin dispatch table */
extern const t_bdispatch  g_builtins[];

int	bi_echo(t_cmd *c, s_env **env);
int	bi_cd(t_cmd *c, s_env **env);
int	bi_pwd(t_cmd *c, s_env **env);
int	bi_export(t_cmd *c, s_env **env);
int	bi_unset(t_cmd *c, s_env **env);
int	bi_env(t_cmd *c, s_env **env);
int	bi_exit(t_cmd *c, s_env **env);

void cleanup_and_exit(s_env **env, t_cmd **cmd, int n);
s_env *find_env_node(s_env *env, const char *key);
void set_env_var(s_env **env, const char *k, const char *v);
void unset_env_var(s_env **env, const char *key);
void sort_env_vars(s_env **env_array, int count);
int count_env_vars(s_env *env);
#endif

