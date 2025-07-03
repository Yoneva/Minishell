/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:50:18 by amsbai            #+#    #+#             */
/*   Updated: 2025/07/03 06:13:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	first_case(t_tokens **node, char *input, t_tokens **cmd)
{
	int			i;
	static int	j;

	i = 0;
	*node = ft_tokenew();
	if (input[i] == '|')
	{
		if (j == 0)
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			g_status = 285;
			return (-1);
		}
		i = pipes(input, i, node);
	}
	else if (input[i] == '<')
		i = redirections2(input, i, node);
	else if (input[i] == '>')
		i = redirections1(input, i, node);
	if (i < 0)
		return (-1);
	ft_tokenadd_back(cmd, *node);
	j = 1;
	return (i);
}

// int	second_case()
// {
// 	int j;
// 	int i;
// }
void	tokenize_shell(char *input, t_tokens **cmd, t_env **listed)
{
	int			i;
	int			j;
	char		*word;
	t_tokens	*node;
	char		*tmp;

	i = 0;
	j = 0;
	if (!input)
	{
		error(input, cmd, listed);
		return ;
	}
	j = 0;
	while (input[i])
	{
		if (ft_isspace((unsigned char)input[i]))
		{
			i++;
			continue ;
		}
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			j = first_case(&node, input + i, cmd);
			if (j < 0)
			{
				error(input, cmd, listed);
				return ;
			}
			i += j;
			continue ;
		}
		node = ft_tokenew();
		node->type = N_WORD;
		word = ft_strdup("");
		if (!word)
		{
			error(input, cmd, listed);
			exit (0);
		}
		while (input[i] && !ft_isspace(input[i]) && input[i] != '|'
			&& input[i] != '<' && input[i] != '>')
		{
			if (input[i] == '\'')
			{
				j = single_quote(input + i, &word, &tmp);
				if (j < 0)
				{
					printf("minishell: syntax error near unexpected token '\''\n");
					g_status = 1;
					error(input, cmd, listed);
					return ;
				}
				i += j;
			}
			else if (input[i] == '"')
			{
				j = double_quote(input + i, &word, &tmp, listed);
				if (j < 0)
				{
					printf("minishell: syntax error near unexpected token '\"'\n");
					g_status = 1;
					error(input, cmd, listed);
					return ;
				}
				i += j;
			}
			else if (input[i] == '$')
			{
				j = if_envariable(input + i, &word, &tmp, listed);
				i += j;
			}
			else
			{
				j = 0;
				tmp = malloc(ft_strlen(word) + 2);
				if (!tmp)
				{
					ft_tokensclear(cmd);
					ft_envclear(listed);
					free(input);
					exit (0);
				}
				ft_memcpy(tmp, word, ft_strlen(word));
				tmp[ft_strlen(word)] = input[i++];
				tmp[ft_strlen(word) + 1] = '\0';
				free(word);
				word = tmp;
			}
		}
		node->value = word;
		ft_tokenadd_back(cmd, node);
	}
}
