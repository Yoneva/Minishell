/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_file2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:10:33 by user              #+#    #+#             */
/*   Updated: 2025/07/01 21:36:03 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nlen(int nbr)
{
	int	i;

    if (nbr == 0)
        return (1);
    i = 0;
    while (nbr != 0)
    {
        nbr /= 10;
        i++;
    }
    return (i);
}

int ft_abs(int nbr)
{
    if (nbr < 0)
        return (-nbr);
    return (nbr);
}

char	*ft_itoa(int nbr)
{
	char	*cnum;
	int		len;
	int		i;

    len = nlen(nbr);
    i = 0;
    if (nbr < 0)
        i++;
    len = len + i;
    cnum = malloc(len + 1);
    if (!cnum)
        return (NULL);
    cnum[0] = '-';
    cnum[len] = '\0';
    while ((len - 1) >= i)
    {
        cnum[len - 1] = ft_abs(nbr % 10) + '0';
        nbr /= 10;
        len--;
    }
    return (cnum);
}
