#ifndef BUILTINS_H
# define BUILTINS_H
# include "../exec/exec.h"
# include "../parssing/minishell.h"

typedef int (*t_bifn)(t_cmd*, s_env**);

int   bi_echo(t_cmd *c, s_env **env);
// int   bi_cd(t_cmd *c, s_env **env);
// int   bi_pwd(t_cmd *c, s_env **env);
// int   bi_export(t_cmd *c, s_env **env);
// int   bi_unset(t_cmd *c, s_env **env);
// int   bi_env(t_cmd *c, s_env **env);
// int   bi_exit(t_cmd *c, s_env **env);

#endif

