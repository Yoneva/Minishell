/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:49:17 by amsbai            #+#    #+#             */
/*   Updated: 2025/05/19 14:49:39 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_realloc(void *str, size_t newsize)
{
	char	*newptr;

	if (str == 0)
		return (malloc(newsize));
	if (newsize == 0)
	{
		free (str);
		return (NULL);
	}
	newptr = malloc(newsize);
	if (!newptr)
		return (NULL);
	ft_memmove(newptr, str, newsize);
	free(str);
	return (newptr);
}