/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:01:28 by amsbai            #+#    #+#             */
/*   Updated: 2025/06/09 19:55:43 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*serachforvar(char *input, s_env **env)
{
	char *str;
	s_env *tmp;
	int len;
	
	tmp = *env;
	len = 0;
	while (input[len] && (ft_isalnum(input[len]) || input[len] == '_'))
	{
		len++;
	}
	str = ft_substr(input , 0, len);
	while (tmp)
	{
		if(ft_strcmp(str, tmp->data) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		return (NULL);
	}
	free (str);
	return (NULL);
}
int	single_quote(char *str, char **word, char **tmp)
{
	int 	j;
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

int	double_quote(char *str, char **word, char **tmp, s_env **env) // had joj dawyin ela rasehm
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
	seg = replace_in_double(seg, env);
	*tmp = ft_strjoin(*word, seg);
	free(*word);
	free(seg);
	*word = *tmp;
	return (i + 1);
}

int	pipes(const char *str, int i, s_tokens **cmd) // For pipe
{
	i += 1;
	if (str[i] == 0)
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (-1);
	}
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == '|' || str[i] == 0)
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			return (-1);
		}
		else
			break;
	}
	(*cmd)->type = N_PIPE;
	(*cmd)->value = ft_strdup("|");
	return (i + 1);
}

int	redirections1(const char *str, int i, s_tokens **cmd) // For append mode && output
{
	if (str[i + 1] == '>')
	{
		(*cmd)->type = N_APPEND_SIGN;
		(*cmd)->value = ft_strdup(">>");
		i++;
	}
	else
	{
		(*cmd)->type = N_OUTPUT_SIGN;
		(*cmd)->value = ft_strdup(">");
	}
	i += 1;
	if (str[i] == 0)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (-1);
	}
	while(str[i])
	{
		if(str[i] == 0)
		{
			printf("minishell: syntax error near unexpected token 'newline'\n");
			return (-1);
		}
		else if (str[i] == ' ')
			i++;
		else
			break;
	}
	return (i);
}

int	redirections2(const char *str, int i, s_tokens **cmd) // For delimiter redirection && input
{
	if(str[i + 1] == '<')
	{
		(*cmd)->type = N_HEREDOC_SIGN;
		(*cmd)->value = ft_strdup("<<");
		i++;
	}
	else
	{
		(*cmd)->type = N_INPUT_SIGN;
		(*cmd)->value = ft_strdup("<");
	}
	i += 1;
	if (str[i] == 0)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (-1);
	}
	while(str[i])
	{
		if(str[i] == 0)
		{
			printf("minishell: syntax error near unexpected token 'newline'\n");
			return (-1);
		}
		else if (str[i] == ' ')
			i++;
		else
			break;
	}
	return (i);
}
