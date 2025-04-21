/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:14:55 by amsbai            #+#    #+#             */
/*   Updated: 2025/04/21 11:20:43 by amsbai           ###   ########.fr       */
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

void	t_lstadd_back(s_tokens **lst, s_tokens *new)
{
	s_tokens	*g;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	g = t_lstlast(*lst);
	g->next = new;
}

// void	f_lstclear(s_env **lst, void (*del)(void*))
// {
// 	s_env	*next;
// 	s_env	*current;

// 	if (!lst || !del)
// 		return ;
// 	current = *lst;
// 	while (current)
// 	{
// 		next = current->next;
// 		// del(current->content);
// 		free(current);
// 		current = next;
// 	}
// 	*lst = NULL;
// }