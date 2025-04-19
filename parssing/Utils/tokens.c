/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:50:18 by amsbai            #+#    #+#             */
/*   Updated: 2025/04/18 18:38:02 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	single_quote(const char *str, int i, s_tokens *cmd)
{
	int j;

	j = i;
	cmd->type = N_SINGLE_QUOTE;
	while(str[i])
	{
		if(str[i] == '\'')
		{
			break ;
		}
		else if(str[i + 1] == 0 && str[i] != '\'')
		{
			//handle error
			printf("uhhh trallallero trallalla :3\n");
			exit(0);
		}
		i++;
	}
	cmd->value = ft_substr(str, j, i - j);
	cmd->len = ft_strlen(cmd->value);
	return (i);
}

int	double_quote(const char *str, int i, s_tokens *cmd)
{
	int j;

	j = i;
	cmd->type = N_DOUBLE_QUOTE;
	while(str[i])
	{
		if(str[i] == '"')
		{
			break ;
		}
		else if(str[i + 1] == 0 && str[i] != '\'')
		{
			//handle error
			printf("uhhh trallallero trallalla :3\n");
			exit(0);
		}
		i++;
	}
	cmd->value = ft_substr(str, j, i - j);
	cmd->len = ft_strlen(cmd->value);
	return (i);
}


void	tokenize_shell(const char* input, char **tokens, s_tokens *cmd)
{
	char *buffer;
	int	i = 0;
	int	j = 0;
	s_tokens *node;

	node = malloc(sizeof(s_tokens));
	while (input[i])
	{
		if (input[i] == '\'')
		{
			i = single_quote(input, i, cmd);
			
		}
		else if (input[i] == '"')
			i = double_quote(input, i, cmd);
		else if (input[i] == '|')
			
		i++;
	}
}
