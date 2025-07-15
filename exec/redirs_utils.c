/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:45:36 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:48:55 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	open_redir_file(t_redir *redir)
{
	if (redir->type == N_HEREDOC_SIGN)
		return (get_heredoc_fd(redir->filename));
	if (redir->type == N_OUTPUT_SIGN)
		return (open(redir->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	if (redir->type == N_APPEND_SIGN)
		return (open(redir->filename, O_CREAT | O_APPEND | O_WRONLY, 0644));
	if (redir->type == N_INPUT_SIGN)
		return (open(redir->filename, O_RDONLY));
	return (-1);
}

static int	get_target_fd(t_redir *redir)
{
	if (redir->type == N_INPUT_SIGN || redir->type == N_HEREDOC_SIGN)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

int	apply_redirs(t_cmd *c)
{
	int	fd;
	int	target_fd;
	int	i;

	i = 0;
	while (i < c->n_redir)
	{
		fd = open_redir_file(&c->redir[i]);
		if (fd < 0)
		{
			perror(c->redir[i].filename);
			return (1);
		}
		target_fd = get_target_fd(&c->redir[i]);
		if (dup2(fd, target_fd) < 0)
		{
			perror("dup2");
			close(fd);
			return (1);
		}
		close(fd);
		i++;
	}
	return (0);
}
