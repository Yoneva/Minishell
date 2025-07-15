/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:19:25 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:19:26 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	free_redir(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->redir)
	{
		while (i < cmd->n_redir)
		{
			free(cmd->redir[i].filename);
			i++;
		}
		free(cmd->redir);
	}
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*next;
	int		i;

	if (!cmd || !*cmd)
		return ;
	while (*cmd)
	{
		next = (*cmd)->next;
		i = 0;
		if ((*cmd)->argv)
		{
			while ((*cmd)->argv[i])
			{
				free((*cmd)->argv[i]);
				i++;
			}
			free((*cmd)->argv);
		}
		free_redir(*cmd);
		free(*cmd);
		*cmd = next;
	}
}

void	cleanup_and_exit(t_env **env, t_cmd **cmd, int n)
{
	free_cmd(cmd);
	ft_envclear(env);
	exit(n);
}
