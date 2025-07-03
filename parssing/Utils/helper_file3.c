/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_file3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 05:06:05 by user              #+#    #+#             */
/*   Updated: 2025/07/03 05:40:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_spaces(const char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

int	set_redirection_type(const char *str, int i, s_tokens **cmd, int cas)
{
	if (cas)
	{
		if (str[i + 1] == '>')
		{
			(*cmd)->type = N_APPEND_SIGN;
			(*cmd)->value = ft_strdup(">>");
			return (i + 2);
		}
		(*cmd)->type = N_OUTPUT_SIGN;
		(*cmd)->value = ft_strdup(">");
	}
	else
	{
		if (str[i + 1] == '<')
		{
			(*cmd)->type = N_HEREDOC_SIGN;
			(*cmd)->value = ft_strdup("<<");
			return (i + 2);
		}
		(*cmd)->type = N_INPUT_SIGN;
		(*cmd)->value = ft_strdup("<");
	}
	return (i + 1);
}

int	handle_redirection(const char *str, int i, s_tokens **cmd, int cas)
{
	i = set_redirection_type(str, i, cmd, cas);
	i = skip_spaces(str, i);
	if (str[i] == 0)
	{
		printf("minishell: syntax error near unexpected token '%c'\n", str[i]);
		g_status = 258;
		return (-1);
	}
	if (str[i] == '>' || str[i] == '<' || str[i] == '|')
	{
		printf("minishell: syntax error near unexpected token '%c'\n", str[i]);
		g_status = 258;
		return (-1);
	}
	return (i);
}

int	redirections1(const char *str, int i, s_tokens **cmd)
{
	return (handle_redirection(str, i, cmd, 1));
}

int	redirections2(const char *str, int i, s_tokens **cmd)
{
	return (handle_redirection(str, i, cmd, 0));
}

