/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:53:47 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/16 14:57:06 by ayousr           ###   ########.fr       */
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
