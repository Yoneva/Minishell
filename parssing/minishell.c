/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:41:51 by amsbai            #+#    #+#             */
/*   Updated: 2025/07/11 20:37:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_env_list(char **env, t_env **list)
{
	int		tmp;
	int		i;
	t_env	*node;

	i = 0;
	while (env[i])
	{
		tmp = find_equale(env[i]);
		if (!tmp)
		{
			ft_envclear(list);
			exit (0);
		}
		node = ft_envnew();
		if (!node)
		{
			ft_envclear(list);
			exit(0);
		}
		node->data = ft_substr(env[i], 0, tmp);
		node->value = ft_substr(env[i], tmp + 1, ft_strlen(env[i]) - tmp);
		ft_envadd_back(list, node);
		node = node->next;
		i++;
	}
}

void	l(void)
{
	system("leaks Minishell");
}

int	init_env(char **env, t_env **listed)
{
	*listed = NULL;
	if (!env || env[0][0] == '\0')
	{
		*listed = malloc(sizeof(t_env));
		if (!*listed)
			return (-1);
		(*listed)->data = NULL;
		(*listed)->value = NULL;
	}
	else
		fill_env_list(env, listed);
	return (0);
}

void	handle_command(char *cmd, t_tokens **tokens, t_cmd **cmds, t_env **list)
{
	if (*cmd)
	{
		add_history(cmd);
		tokenize_shell(cmd, tokens, list);
		if (*tokens)
		{
			*cmds = parse_cmd(*tokens);
			if (*cmds)
			{
				if ((*cmds)->next)
					exec_pipeline(*cmds, list);
				else
					exec_single(cmds, list);
				free_cmd(cmds);
			}
		}
		ft_tokensclear(tokens);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env		*listed;
	t_tokens	*tokens;
	t_cmd		*commands;
	char		*cmd;

	tokens = NULL;
	commands = NULL;
	if (ac != 1 || init_env(env, &listed) < 0)
		return (0);
	(void)av;
	(void)ac;
	// atexit(l);
	while (1)
	{
		cmd = readline(">> ");
		if (!cmd)
			break ;
		handle_command(cmd, &tokens, &commands, &listed);
		free(cmd);
	}
	ft_envclear(&listed);
	return (0);
}
