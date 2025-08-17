/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:50:18 by amsbai            #+#    #+#             */
/*   Updated: 2025/08/17 23:37:06 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../builtins/builtins.h"
#include "../../builtins/status.h"

int	if_envariable(char *str, char **word, t_env **env)
{
	int		i;
	char	*replaced;
	char	*seg;
	char	*tmp;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'
			|| str[i] == '$' || str[i] == '?'))
		i++;
	seg = ft_substr(str, 0, i);
	replaced = replace_in_double(0, 0, seg, env);
	free(seg);
	if (!replaced)
		replaced = ft_strdup("");
	tmp = ft_strjoin(*word, replaced);
	free(*word);
	free(replaced);
	*word = tmp;
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
			set_status(285);
			return (-1);
		}
		i = pipes(input, i, node);
		*has_word = 0;
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
	int				i;
	int				j;
	t_token_context	ctx;

	i = 0;
	ctx.has_word = 0;
	ctx.listed = listed;
	ctx.cmd = cmd;
	if (!input)
		return (ft_tokensclear(cmd));
	while (input[i])
	{
		if (ft_isspace((unsigned char)input[i]))
			i++;
		else
		{
			j = process_token(input, i, &ctx);
			if (j < 0)
				ft_tokensclear(cmd);
			i = j;
		}
	}
}
