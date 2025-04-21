/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:41:51 by amsbai            #+#    #+#             */
/*   Updated: 2025/04/21 17:16:41 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (-1);
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
	s_env	*listed = NULL;
	s_tokens *tokens = NULL;
	
	char *cmd;
	cmd = readline(">> ");
	fill_env_list(env, &listed);
	tokenize_shell(cmd,&tokens);
	printf("%s\n", cmd);
	while(tokens)
	{
		printf("%d = %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
	return (0);
}