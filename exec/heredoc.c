/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:45:33 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 03:03:18 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	heredoc_loop(int write_fd, const char *limiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			return (0);
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			return (0);
		}
		if (write(write_fd, line, ft_strlen(line)) == -1 || \
			write(write_fd, "\n", 1) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

int	get_heredoc_fd(const char *limiter)
{
	int	p[2];

	if (pipe(p) == -1)
	{
		perror("pipe");
		return (-1);
	}
	if (heredoc_loop(p[1], limiter) == -1)
	{
		close(p[1]);
		close(p[0]);
		return (-1);
	}
	close(p[1]);
	return (p[0]);
}
