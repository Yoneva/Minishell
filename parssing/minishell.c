/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:41:51 by amsbai            #+#    #+#             */
/*   Updated: 2025/05/04 19:01:29 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../exec/exec.h"
#include "../builtins/builtins.h"

void free_env_list(s_env *env);
void free_tokens(s_tokens *tok);
void free_cmd(t_cmd *cmd);

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
			f_lstclear(list);
			exit (0);
		}
		node = f_lstnew();
		if (!node)
		{
			f_lstclear(list);
			exit(0);
		}
		node->data = ft_substr(env[i],0, tmp);
		node->value = ft_substr(env[i],tmp + 1, ft_strlen(env[i]) - tmp);
		f_lstadd_back(list, node);
		node = node->next;
		i++;
	}
}

int main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	s_env		*listed = NULL;
	s_tokens	*tokens = NULL;
	t_cmd		*commands = NULL;
	char *cmd;

	// g_env_list = NULL;
	// g_tokens   = NULL;
	// g_cmds     = NULL;
	fill_env_list(env, &listed);
	g_env_list = listed;
	while (1)
	{
		cmd = readline(">> ");
		if (cmd[0] == 0)
		{
			free(cmd);
			continue;
		}
		tokenize_shell(cmd, &tokens, &listed);
		s_tokens *tmp = tokens;
		while (tmp)
		{
			printf("%d = %s\n", tmp->type, tmp->value);
			tmp = tmp->next;
		}
		commands = parse_cmd(tokens);
		if (!commands)
		{
			fprintf(stderr, "parse_commands: empty or malloc failure\n");
			return (EXIT_FAILURE);
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
			printf("\n");
			int j = 0;
			while (j < curr->n_redir)
			{
				// printf("redir[%d]: type = %d, filename = %s\n",
				// j, curr->redir[j].type, curr->redir[j].filename);
				j++;
			}
			curr = curr->next;
		}
		exec_single(commands, &listed);
		free_cmd(commands);
		free_tokens(tokens);
		tokens = NULL;
	}
    free_env_list(listed);
	return (0);
}