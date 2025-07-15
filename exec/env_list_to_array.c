/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:44:01 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:50:35 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/minishell.h"

/* count nodes */
static int	env_len(t_env *lst)
{
	int	n;

	n = 0;
	while (lst)
	{
		n++;
		lst = lst->next;
	}
	return (n);
}

/* join KEY + '=' + VALUE into a freshly‑allocated string */
static char	*join_kv(t_env *node)
{
	char	*tmp;
	char	*pair;

	tmp = ft_strjoin(node->data, "=");
	if (!tmp)
		return (NULL);
	pair = ft_strjoin(tmp, node->value);
	free(tmp);
	return (pair);
}

/* public helper – caller must free the array afterwards */
char	**env_list_to_array(t_env *lst)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (env_len(lst) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (lst)
	{
		arr[i++] = join_kv(lst);
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	free_strarray(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
