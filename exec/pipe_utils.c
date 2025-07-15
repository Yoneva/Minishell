/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:45:30 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:45:31 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/wait.h>
#include <fcntl.h>

int	pipe_count(t_cmd *c)
{
	int	n;

	n = 0;
	while (c)
	{
		n++;
		c = c->next;
	}
	return (n - 1);
}

/* open *n* pipes (n ≥ 0). Return 0 on success, -1 on failure */
int	open_all_pipes(int n, int p[][2])
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pipe(p[i]) == -1)
		{
			while (i--)
			{
				close(p[i][0]);
				close(p[i][1]);
			}
			return (-1);
		}
		i++;
	}
	return (0);
}

void	close_all_pipes(int n, int p[][2])
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(p[i][0]);
		close(p[i][1]);
		i++;
	}
}
