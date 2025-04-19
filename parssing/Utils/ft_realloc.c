/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:37:24 by amsbai            #+#    #+#             */
/*   Updated: 2025/04/10 18:54:18 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_realloc(void *str, size_t newsize)
{
	char	*newptr;

	if (str == 0)
		return (malloc(newsize * sizeof(long)));
	if (newsize == 0)
	{
		free (str);
		return (NULL);
	}
	newptr = malloc(newsize * sizeof(long));
	if (!newptr)
		return (NULL);
	ft_memmove(newptr, str, newsize * sizeof(long));
	free(str);
	return (newptr);
}
