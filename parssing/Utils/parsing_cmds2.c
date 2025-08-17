/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 22:28:40 by user              #+#    #+#             */
/*   Updated: 2025/08/17 22:36:16 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../builtins/builtins.h"
#include "../../builtins/status.h"

int	it_redir(int sign)
{
	return (sign == N_INPUT_SIGN || sign == N_OUTPUT_SIGN
		|| sign == N_APPEND_SIGN || sign == N_HEREDOC_SIGN);
}

int	count_args(t_tokens *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != N_PIPE)
	{
		if (tok->type == N_WORD || tok->type == N_DOUBLE_QUOTE
			|| tok->type == N_SINGLE_QUOTE)
			count++;
		tok = tok->next;
	}
	return (count);
}

int	count_redirs(t_tokens *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != N_PIPE)
	{
		if (it_redir(tok->type))
			count++;
		tok = tok->next;
	}
	return (count);
}

int	builtin_id(const char *word)
{
	int	i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (!ft_strcmp(word, g_builtins[i].name))
			return (i);
		i++;
	}
	return (-1);
}

void	init_cmd_struct(t_cmd *cmd, int argc, int rcount)
{
	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->argv)
	{
		cmd->redir = NULL;
		return ;
	}
	cmd->redir = malloc(sizeof(t_redir) * rcount);
	if (!cmd->redir)
	{
		free(cmd->argv);
		cmd->argv = NULL;
		return ;
	}
	cmd->n_redir = rcount;
	cmd->builtin_id = -1;
	cmd->next = NULL;
}
