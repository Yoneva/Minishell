/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:26:34 by user              #+#    #+#             */
/*   Updated: 2025/07/03 06:33:44 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../builtins/builtins.h"

static int	it_redir(int sign)
{
	return (sign == N_INPUT_SIGN || sign == N_OUTPUT_SIGN
		|| sign == N_APPEND_SIGN || sign == N_HEREDOC_SIGN);
}

static int	count_args(t_tokens *tok)
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

static int	count_redirs(t_tokens *tok)
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

static int	builtin_id(const char *word)
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

static void	init_cmd_struct(t_cmd *cmd, int argc, int rcount)
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

static void	fill_cmd_struct(t_cmd *cmd, t_tokens **tokp)
{
	int			argt_i;
	int			redirt_i;
	t_tokens	*tok;

	tok = *tokp;
	argt_i = 0;
	redirt_i = 0;
	while (tok && tok->type != N_PIPE)
	{
		if (tok->type == N_WORD || tok->type == N_DOUBLE_QUOTE
			|| tok->type == N_SINGLE_QUOTE)
			cmd->argv[argt_i++] = ft_strdup(tok->value);
		else if (it_redir(tok->type))
		{
			if (!tok->next || tok->next->type == N_PIPE)
			{
				fprintf(stderr,
					"minishell: syntax error near unexpected token `newline'\n");
				g_status = 1;
				// should handle syntax error | free everything that been used
				return ;
			}
			cmd->redir[redirt_i].type = tok->type;
			tok = tok->next;
			cmd->redir[redirt_i++].filename = ft_strdup(tok->value);
		}
		tok = tok->next;
	}
	cmd->argv[argt_i] = NULL;
	cmd->n_redir = redirt_i;
	// Set builtin_id if we have a command
	if (cmd->argv[0])
		cmd->builtin_id = builtin_id(cmd->argv[0]);
	if (tok && tok->type == N_PIPE)
		tok = tok->next;
	*tokp = tok;
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
	fill_cmd_struct(cmd, tokens);
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
		if (!head)
			head = curr;
		else
			prev->next = curr;
		prev = curr;
	}
	ft_tokensclear(&tokens);
	return (head);
}
