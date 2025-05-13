/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:41:51 by amsbai            #+#    #+#             */
/*   Updated: 2025/05/13 17:16:18 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_tosawi(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	fill_env_list(char **env, s_env **list)
{
	int		tmp;
	int		i;
	s_env	*node;
	
	i = 0;
	while(env[i])
	{
		tmp = find_tosawi(env[i]);
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
		node->data = ft_substr(env[i],0, tmp);
		node->value = ft_substr(env[i],tmp + 1, ft_strlen(env[i]) - tmp);
		ft_envadd_back(list, node);
		node = node->next;
		i++;
	}
}

int main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	s_env		*listed;
	s_tokens	*tokens;
	t_cmd		*commands ;
	char *cmd;

	listed = NULL;
	tokens = NULL;
	commands = NULL;
	fill_env_list(env, &listed);
	while (1)
	{
		cmd = readline(">> ");
		if (!cmd)
			break;
		if (cmd[0] == 0)
		{
			free(cmd);
			continue;
		}
		if (*cmd == '\0')
		{
			free(cmd);
			continue;
		}
		add_history(cmd);
		tokenize_shell(cmd, &tokens, &listed);
		commands = parse_cmd(tokens);
		if (!commands)
		{
			fprintf(stderr, "parse_commands: empty or malloc failure\n");
			ft_tokensclear(&tokens);
			free(cmd);
			continue;
		}
		t_cmd *curr = commands;
		while (curr)
		{
			int i = 0;
			while (curr->argv && curr->argv[i])
			{
				// printf("arg=%d  =>  [%s] ", i, curr->argv[i]);
				i++;
			}
			// printf("\n");
			int j = 0;
			while (j < curr->n_redir)
			{
				// printf("redir[%d]: type = %d, filename = %s\n",
				// j, curr->redir[j].type, curr->redir[j].filename);
				j++;
			}
			curr = curr->next;
		}
		if (commands->next)
			exec_pipeline(commands, &listed);
		else
			exec_single(&commands, &listed);
		free_cmd(&commands);
		ft_tokensclear(&tokens);
		tokens = NULL;
	}
   ft_envclear(&listed);
	return (0);
}