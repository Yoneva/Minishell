/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 23:41:40 by user              #+#    #+#             */
/*   Updated: 2025/08/17 23:42:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/minishell.h"

static int	g_status = 0;

int	get_status(void)
{
	return (g_status);
}

void	set_status(int status)
{
	g_status = status;
}
