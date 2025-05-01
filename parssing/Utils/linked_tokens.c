/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:14:55 by amsbai            #+#    #+#             */
/*   Updated: 2025/04/30 17:40:37 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

s_tokens	*t_lstnew(void)
{
	s_tokens	*node;

	node = malloc(sizeof(s_tokens));
	if (!node)
		return (NULL);
	node->next = NULL;
	return (node);
}

s_tokens	*t_lstlast(s_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	t_lstadd_back(s_tokens **lst, s_tokens *new_node)
{
	s_tokens	*g;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	g = t_lstlast(*lst);
	g->next = new_node;
}

void	t_lstclear(s_tokens **lst)
{
	s_tokens	*next;
	s_tokens	*current;

	if (!lst)
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