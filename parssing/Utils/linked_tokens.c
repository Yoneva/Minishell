/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:14:55 by amsbai            #+#    #+#             */
/*   Updated: 2025/06/24 21:05:52 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

s_tokens	*ft_tokenew(void)
{
 	s_tokens	*node;

 	node = malloc(sizeof(s_tokens));
 	if (!node)
 		return (NULL);
 	node->value = NULL;
 	node->type = 0;
 	node->next = NULL;
	return (node);
}

s_tokens	*ft_tokenlast(s_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_tokenadd_back(s_tokens **lst, s_tokens *new_node)
{
	s_tokens	*g;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	g = ft_tokenlast(*lst);
	g->next = new_node;
}

void	ft_tokensclear(s_tokens **lst)
{
	s_tokens	*next;
	s_tokens	*current;

	if (lst == NULL || (*lst) == NULL)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*lst = NULL;
}
