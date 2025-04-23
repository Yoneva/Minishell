/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimaneyousr <aimaneyousr@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:41:51 by amsbai            #+#    #+#             */
/*   Updated: 2025/04/23 12:08:01 by aimaneyousr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../exec/exec.h"

int	find_tosawi(char *str)
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
			//handle failure
			printf("apah! 7z9at eliya hna #1");
			exit (0);
		}
		node = f_lstnew();
		if (!node)
		{
			//handle failure
			printf("apah! 7z9at eliya hna #2");
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
	t_cmd		*commands;
	
	char *cmd;
	cmd = readline(">> ");
	fill_env_list(env, &listed);
	tokenize_shell(cmd,&tokens);
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
	int global_status;
	global_status = exec_single(commands, &listed);
	(void)global_status;
	
	// printf("%s\n", cmd);
	// while(tokens)
	// {
	// 	printf("%d = %s\n", tokens->type, tokens->value);
	// 	tokens = tokens->next;
	// }
	
	return (0);
}