/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:18:56 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:26:12 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../parssing/minishell.h"

void	sort_env_vars(t_env **env_array, int count)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env_array[j]->data, env_array[j + 1]->data) > 0)
			{
				temp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*node;

	count = 0;
	node = env;
	while (node)
	{
		count++;
		node = node->next;
	}
	return (count);
}

t_env	*find_env_node(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->data, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	set_env_var(t_env **env, const char *k, const char *v)
{
	t_env	*node;
	t_env	*new;

	node = find_env_node(*env, k);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(v);
	}
	else
	{
		new = ft_envnew();
		if (!new)
			return ;
		new->data = ft_strdup(k);
		new->value = ft_strdup(v);
		ft_envadd_back(env, new);
	}
}

void	unset_env_var(t_env **env, const char *key)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->data, key))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->data);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
