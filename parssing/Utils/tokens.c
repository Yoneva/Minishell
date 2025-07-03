/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:50:18 by amsbai            #+#    #+#             */
/*   Updated: 2025/07/03 07:19:04 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../builtins/builtins.h"

#include "../minishell.h"
#include "../../builtins/builtins.h"

void	error(char *input, t_tokens **cmd, t_env **listed)
{
	ft_tokensclear(cmd);
	ft_envclear(listed);
	free(input);
}

int	if_envariable(char *str, char **word, char **tmp, t_env **env)
{
	int		i;
	char	*seg;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'
			|| str[i] == '$' || str[i] == '?'))
		i++;
	seg = ft_substr(str, 0, i);
	seg = replace_in_double(0, 0, seg, env);
	if (!seg)
		seg = ft_strdup("");
	*tmp = ft_strjoin(*word, seg);
	free(*word);
	free(seg);
	*word = *tmp;
	return (i);
}

int	first_case(t_tokens **node, char *input, t_tokens **cmd, int *has_word)
{
	int	i;

	i = 0;
	*node = ft_tokenew();
	if (input[i] == '|')
	{
		if (*has_word == 0)
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			g_status = 285;
			return (-1);
		}
		i = pipes(input, i, node);
		*has_word = 0;// Reset after pipe
	}
	else if (input[i] == '<')
		i = redirections2(input, i, node);
	else if (input[i] == '>')
		i = redirections1(input, i, node);
	if (i < 0)
		return (-1);
	ft_tokenadd_back(cmd, *node);
	return (i);
}

void	tokenize_shell(char *input, t_tokens **cmd, t_env **listed)
{
	int	i;
	int	j;
	int	has_word;

	i = 0;
	has_word = 0;
	if (!input)
		return (error(input, cmd, listed));
	while (input[i])
	{
		if (ft_isspace((unsigned char)input[i]))
			i++;
		else
		{
			j = process_token(input, i, cmd, listed, &has_word);
			if (j < 0)
				return (error(input, cmd, listed));
			i = j;
		}
	}
}
