/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:01:28 by amsbai            #+#    #+#             */
/*   Updated: 2025/08/17 23:37:47 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../builtins/status.h"

int	single_quote(char *str, char **word, char **tmp)
{
	int		j;
	int		i;
	char	*seg;

	i = 1;
	j = i;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] != '\'')
		return (-1);
	seg = substr_quotes(str, j, i - j, 0);
	*tmp = ft_strjoin(*word, seg);
	free(*word);
	free(seg);
	*word = *tmp;
	return (i + 1);
}

int	double_quote(char *str, char **word, char **tmp, t_env **env)
{
	int		i;
	char	*seg;
	char	*replaced;

	i = 1;
	if (!str[i] || str[i] == '\0')
		return (-1);
	while (str[i] && str[i] != '"')
		i++;
	if (str[i] != '"')
		return (-1);
	seg = substr_quotes(str, 1, i - 1, 0);
	replaced = replace_in_double(0, 0, seg, env);
	free(seg);
	*tmp = ft_strjoin(*word, replaced);
	free(*word);
	free(replaced);
	*word = *tmp;
	return (i + 1);
}

int	pipes(const char *str, int i, t_tokens **cmd)
{
	i += 1;
	i = skip_spaces(str, i);
	if (str[i] == 0)
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		set_status(258);
		return (-1);
	}
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == '|' || str[i] == 0)
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			set_status(258);
			return (-1);
		}
		else
			break ;
	}
	(*cmd)->type = N_PIPE;
	(*cmd)->value = ft_strdup("|");
	return (i);
}
