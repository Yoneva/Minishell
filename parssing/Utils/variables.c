/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:44:14 by user              #+#    #+#             */
/*   Updated: 2025/07/09 18:12:32 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*handle_question_mark(void)
{
	char	*result;

	result = ft_itoa(g_status);
	g_status = 0;
	return (result);
}

static char	*search_env_list(t_env *tmp, char **str)
{
	char	*result;

	while (tmp)
	{
		if (ft_strcmp(*str, tmp->data) == 0)
		{
			result = ft_strdup(tmp->value);
			free(*str);
			return (result);
		}
		tmp = tmp->next;
	}
	free(*str);
	return (NULL);
}

void	*serachforvar(char *input, t_env **env)
{
	char	*str;
	int		len;

	if (input[0] == '?')
		return (handle_question_mark());
	len = 0;
	while (input[len] && (ft_isalnum(input[len])
			|| input[len] == '_') && input[len] != '?')
		len++;
	str = ft_substr(input, 0, len);
	return (search_env_list(*env, &str));
}
