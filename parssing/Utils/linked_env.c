/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:14:55 by amsbai            #+#    #+#             */
/*   Updated: 2025/04/20 12:41:09 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

s_env	*f_lstnew(void)
{
	s_env	*node;

	node = malloc(sizeof(s_env));
	if (!node)
		return (NULL);
	node->next = NULL;
	return (node);
}

s_env	*f_lstlast(s_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	f_lstadd_back(s_env **lst, s_env *new)
{
	s_env	*g;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	g = f_lstlast(*lst);
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