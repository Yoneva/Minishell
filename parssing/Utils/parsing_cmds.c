/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:26:34 by user              #+#    #+#             */
/*   Updated: 2025/08/18 00:22:01 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../builtins/builtins.h"
#include "../../builtins/status.h"

static void	free_cmd_on_error(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = -1;
		while (cmd->argv[++i])
			free(cmd->argv[i]);
		free(cmd->argv);
	}
	if (cmd->redir)
	{
		i = 0;
		while (i < cmd->n_redir)
		{
			if (cmd->redir[i].filename)
				free(cmd->redir[i].filename);
			i++;
		}
		free(cmd->redir);
	}
	free(cmd);
}

static int	proces_token(t_cmd *cmd, t_tokens **tok, int *argt_i, int *redirt_i)
{
	if ((*tok)->type == N_WORD || (*tok)->type == N_DOUBLE_QUOTE
		|| (*tok)->type == N_SINGLE_QUOTE)
	{
		cmd->argv[(*argt_i)++] = ft_strdup((*tok)->value);
	}
	else if (it_redir((*tok)->type))
	{
		if (!(*tok)->next || (*tok)->next->type == N_PIPE)
			return (handle_syntax_error());
		cmd->redir[*redirt_i].type = (*tok)->type;
		*tok = (*tok)->next;
		cmd->redir[(*redirt_i)++].filename = ft_strdup((*tok)->value);
	}
	return (0);
}

static int	fill_cmd_struct(t_cmd *cmd, t_tokens **tokp)
{
	int			argt_i;
	int			redirt_i;
	t_tokens	*tok;

	tok = *tokp;
	argt_i = 0;
	redirt_i = 0;
	while (tok && tok->type != N_PIPE)
	{
		if (proces_token(cmd, &tok, &argt_i, &redirt_i) < 0)
			return (-1);
		tok = tok->next;
	}
	cmd->argv[argt_i] = NULL;
	cmd->n_redir = redirt_i;
	if (cmd->argv[0])
		cmd->builtin_id = builtin_id(cmd->argv[0]);
	if (tok && tok->type == N_PIPE)
		tok = tok->next;
	*tokp = tok;
	return (0);
}

static t_cmd	*build_one_cmd(t_tokens **tokens)
{
	t_cmd	*cmd;
	int		argc;
	int		rcount;

	argc = count_args(*tokens);
	rcount = count_redirs(*tokens);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd_struct(cmd, argc, rcount);
	if (!cmd->argv || !cmd->redir)
	{
		free_cmd_on_error(cmd);
		return (NULL);
	}
	if (fill_cmd_struct(cmd, tokens) < 0)
	{
		free_cmd_on_error(cmd);
		return (NULL);
	}
	return (cmd);
}

t_cmd	*parse_cmd(t_tokens *tokens)
{
	t_cmd	*head;
	t_cmd	*prev;
	t_cmd	*curr;

	head = NULL;
	prev = NULL;
	while (tokens)
	{
		curr = build_one_cmd(&tokens);
		if (!curr)
		{
			free_cmd(&head);
			return (NULL);
		}
		if (!head)
			head = curr;
		else
			prev->next = curr;
		prev = curr;
	}
	return (head);
}
