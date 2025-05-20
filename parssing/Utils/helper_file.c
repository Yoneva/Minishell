/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:01:28 by amsbai            #+#    #+#             */
/*   Updated: 2025/05/19 16:54:15 by amsbai           ###   ########.fr       */
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
		printf("minishell: undefined variable: $%s\n", str);
	free (str);
	return (NULL);
}
int	single_quote(const char *str, int i, s_tokens **cmd)
{
	int j;

	j = i;
	while(str[i])
	{
		if(str[i] == '\'')
			break ;
		else if(str[i] == 0)
		{
			printf("minishell: syntax error: unmatched single quote\n");
			return (-1);
		}
		i++;
	}
	(*cmd)->type = N_WORD;
	(*cmd)->value = ft_substr(str, j, i - j);
	return (i + 1);
}

int	double_quote(char *str, int i, s_tokens **cmd, s_env **env) // had joj dawyin ela rasehm
{
	int j;

	j = 1;
	while(str[j])
	{
		if(str[j] == '"')
			break ;
		else if(str[j] == 0)
		{
			printf("minishell: syntax error: unmatched double quote\n");
			return (-1);
		}
		j++;
		i++;
	}
	(*cmd)->type = N_WORD;
	(*cmd)->value = replace_in_double(str + 1, env);
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
