/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimaneyousr <aimaneyousr@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:14:55 by amsbai            #+#    #+#             */
/*   Updated: 2025/04/22 03:40:46 by aimaneyousr      ###   ########.fr       */
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

void	f_lstadd_back(s_env **lst, s_env *new_node)
{
	s_env	*g;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	g = f_lstlast(*lst);
	g->next = new_node;
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