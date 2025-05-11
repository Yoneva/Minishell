/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:14:55 by amsbai            #+#    #+#             */
/*   Updated: 2025/05/08 15:18:14 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

s_env	*ft_envnew(void)
{
	s_env	*node;

	node = malloc(sizeof(s_env));
	if (!node)
		return (NULL);
	node->next = NULL;
	return (node);
}

s_env	*ft_envlast(s_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_envadd_back(s_env **lst, s_env *new_node)
{
	s_env	*g;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	g = ft_envlast(*lst);
	g->next = new_node;
}

void	ft_envclear(s_env **lst)
{
	s_env	*next;
	s_env	*current;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current->data);
		free(current);
		current = next;
	}
	*lst = NULL;
}