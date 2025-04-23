/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimaneyousr <aimaneyousr@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 02:12:08 by amsbai            #+#    #+#             */
/*   Updated: 2025/04/21 14:52:56 by aimaneyousr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*g;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	g = ft_lstlast(*lst);
	g->next = new;
}

// #include "ft_lstnew_bonus.c"
// int main()
// {
// 	t_list *node1;
// 	t_list *new;

// 	new = ft_lstnew("apah");

// 	node1 = NULL;
// 	ft_lstadd_back(&node1, new);
// 	printf("%s", node1->content);
// }
