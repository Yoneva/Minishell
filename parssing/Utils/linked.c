/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:14:55 by amsbai            #+#    #+#             */
/*   Updated: 2025/04/19 11:45:18 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*f_lstnew(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->str = NULL; 
	node->next = NULL;
	return (node);
}

t_node	*f_lstlast(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	f_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*g;

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