/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:19:21 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:42:40 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../parssing/minishell.h"
# include "../exec/exec.h"

/*
** Builtin function pointer
*/
typedef int					(*t_builtin_fn)(t_cmd *cmd, t_env **env);

/*
** Dispatch table for builtins
*/
typedef struct s_bdispatch
{
	char					*name;
	t_builtin_fn			fn;
}							t_bdispatch;

const t_bdispatch	*get_builtins(void);

int							bi_echo(t_cmd *c, t_env **env);
int							bi_cd(t_cmd *c, t_env **env);
int							bi_pwd(t_cmd *c, t_env **env);
int							bi_export(t_cmd *c, t_env **env);
int							bi_unset(t_cmd *c, t_env **env);
int							bi_env(t_cmd *c, t_env **env);
int							bi_exit(t_cmd *c, t_env **env);

void						cleanup_and_exit(t_env **env, t_cmd **cmd, int n);
t_env						*find_env_node(t_env *env, const char *key);
void						set_env_var(t_env **env, const char *k,
								const char *v);
void						unset_env_var(t_env **env, const char *key);
void						sort_env_vars(t_env **env_array, int count);
int							count_env_vars(t_env *env);
#endif
