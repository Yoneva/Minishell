/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:01:28 by amsbai            #+#    #+#             */
/*   Updated: 2025/07/03 06:08:45 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*serachforvar(char *input, t_env **env)
{
	char	*str;
	t_env	*tmp;
	int		len;

	tmp = *env;
	len = 0;
	while (input[len] && (ft_isalnum(input[len])
			|| input[len] == '_') && input[len] != '?')
		len++;
	if (input[0] == '?')
	{
		str = ft_itoa(g_status);
		g_status = 0;
		return (str);
	}
	str = ft_substr(input, 0, len);
	while (tmp)
	{
		if (ft_strcmp(str, tmp->data) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	free (str);
	return (NULL);
}

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
	int		j;
	char	*seg;

	i = 1;
	j = i;
	if (!str[i])
		return (-1);
	while (str[i] && str[i] != '"') // wont work in false cases
		i++;
	if (str[i] != '"')
		return (-1);
	seg = substr_quotes(str, j, i - j, 0);
	seg = replace_in_double(0, 0, seg, env);
	*tmp = ft_strjoin(*word, seg);
	free(*word);
	free(seg);
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
		g_status = 258;
		return (-1);
	}
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == '|' || str[i] == 0)
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			g_status = 258;
			return (-1);
		}
		else
			break ;
	}
	(*cmd)->type = N_PIPE;
	(*cmd)->value = ft_strdup("|");
	return (i);
}
