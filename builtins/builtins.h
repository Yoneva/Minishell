#ifndef BUILTINS_H
# define BUILTINS_H
# include "../exec/exec.h"
# include "../parssing/minishell.h"

typedef int (*t_bifn)(t_cmd*, s_env**);

int   bi_echo(t_cmd *c, s_env **env);
int   bi_cd(t_cmd *c, s_env **env);
int   bi_pwd(t_cmd *c, s_env **env);
int   bi_export(t_cmd *c, s_env **env);
int   bi_unset(t_cmd *c, s_env **env);
int   bi_env(t_cmd *c, s_env **env);
int   bi_exit(t_cmd *c, s_env **env);

void free_env_list(s_env *env);
void free_tokens(s_tokens *tok);
void free_cmd(t_cmd *cmd);
void cleanup_and_exit(int code);

s_env *find_env_node(s_env *env, const char *key);
void set_env_var(s_env **env, const char *k, const char *v);
void unset_env_var(s_env **env, const char *key);

#endif

