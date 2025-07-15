/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:19:49 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:36:32 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../parssing/minishell.h"

static void	print_export_line(t_env *env_var)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env_var->data, STDOUT_FILENO);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	ft_putstr_fd(env_var->value, STDOUT_FILENO);
	ft_putstr_fd("\"\n", STDOUT_FILENO);
}

static void	fill_env_array(t_env *env, t_env **env_array)
{
	int	i;

	i = 0;
	while (env)
	{
		env_array[i] = env;
		i++;
		env = env->next;
	}
}

static int	print_sorted_env(t_env **env)
{
	int		count;
	t_env	**env_array;
	int		i;

	count = count_env_vars(*env);
	env_array = malloc(sizeof(t_env *) * count);
	if (!env_array)
	{
		perror("export: malloc");
		return (1);
	}
	fill_env_array(*env, env_array);
	sort_env_vars(env_array, count);
	i = 0;
	while (i < count)
	{
		print_export_line(env_array[i]);
		i++;
	}
	free(env_array);
	return (0);
}

static void	add_or_update_env(char *arg, t_env **env)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*eq = '\0';
		set_env_var(env, arg, eq + 1);
		*eq = '=';
	}
	else
		set_env_var(env, arg, "");
}

int	bi_export(t_cmd *c, t_env **env)
{
	int	i;

	i = 1;
	if (!c->argv[i])
		return (print_sorted_env(env));
	while (c->argv[i])
	{
		add_or_update_env(c->argv[i], env);
		i++;
	}
	return (0);
}
