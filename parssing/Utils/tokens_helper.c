/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:52:35 by user              #+#    #+#             */
/*   Updated: 2025/07/03 07:22:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../builtins/builtins.h"

int	handle_normal_char(char *input, char **word, int i)
{
	char	*tmp;
	int		len;

	len = ft_strlen(*word);
	tmp = malloc(len + 2);
	if (!tmp)
		return (-1);
	ft_memcpy(tmp, *word, len);
	tmp[len] = input[i];
	tmp[len + 1] = '\0';
	free(*word);
	*word = tmp;
	return (i + 1);
}

int	handle_quotes(char *input, char **word, char **tmp, t_env **listed, int i)
{
	int	j;

	if (input[i] == '\'')
		j = single_quote(input + i, word, tmp);
	else
		j = double_quote(input + i, word, tmp, listed);
	if (j < 0)
		return (-1);
	return (j);
}

int	process_word_loop(char *input, int i, char **word, t_env **listed)
{
	char	*tmp;
	int		j;

	while (input[i] && !ft_isspace(input[i]) && input[i] != '|'
		&& input[i] != '<' && input[i] != '>')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			j = handle_quotes(input, word, &tmp, listed, i);
			if (j < 0)
				return (-1);
			i += j;
		}
		else if (input[i] == '$')
		{
			j = if_envariable(input + i, word, &tmp, listed);
			i += j;
		}
		else
			i = handle_normal_char(input, word, i);
	}
	return (i);
}

int	process_word(char *input, int i, t_tokens **cmd, t_env **listed)
{
	t_tokens	*node;
	char		*word;

	node = ft_tokenew();
	node->type = N_WORD;
	word = ft_strdup("");
	i = process_word_loop(input, i, &word, listed);
	if (i < 0)
		return (-1);
	node->value = word;
	ft_tokenadd_back(cmd, node);
	return (i);
}
