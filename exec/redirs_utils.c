/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:45:36 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 04:42:15 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../builtins/status.h"

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

static int	process_single_redirection(t_redir *redir)
{
	int	fd;
	int	target_fd;

	fd = open_redir_file(redir);
	if (fd < 0)
	{
		if (redir->type == N_HEREDOC_SIGN && get_status() == 130)
			return (2);
		perror(redir->filename);
		return (1);
	}
	target_fd = get_target_fd(redir);
	if (dup2(fd, target_fd) < 0)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	apply_redirs(t_cmd *c)
{
	int	i;
	int	ret;

	i = 0;
	while (i < c->n_redir)
	{
		ret = process_single_redirection(&c->redir[i]);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}
