/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:42:42 by amsbai            #+#    #+#             */
/*   Updated: 2025/07/03 07:23:03 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*helper_fun(int i, const char *input, char *result)
{
	char	*s;

	s = malloc(2);
	if (!s)
		return (NULL);
	s[0] = input[i];
	s[1] = '\0';
	result = ft_strjoin(result, s);// add char to result
	free(s);
	return (result);
}

void	*if_dollar_sign(int i, char *result, char *input, t_env **env)
{
	char	*tmp;

	i += 1;
	tmp = serachforvar(input + i, env); // Search for variable in env list
	if (tmp)
		return (ft_strjoin(result, tmp)); // Add value to result
	else
		return (NULL);
}

char	*replace_in_double(int i, int j, char *input, t_env **env)
{
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '$')
		{
			result = if_dollar_sign(i, result, input, env);
			if (!result)
				return (NULL);
			j = i++;
			while (input[i] && (ft_isalnum(input[i])
					|| input[i] == '_' || input[j] == '?'))
				i++;// skip variable name
		}
		else if (input[i] == '"')
			break ;
		else // Regular character
		{
			result = helper_fun(i, input, result);
			i++;
		}
	}
	return (result);
}

int	process_token(char *input, int i, t_tokens **cmd, t_env **listed, int *has_word)
{
	int			j;
	t_tokens	*node;

	if (input[i] == '|' || input[i] == '<' || input[i] == '>')
	{
		j = first_case(&node, input + i, cmd, has_word);
		if (j < 0)
			return (-1);
		return (i + j);
	}
	else
	{
		j = process_word(input, i, cmd, listed);
		if (j < 0)
			return (-1);
		*has_word = 1;
		return (j);
	}
}

// int main()
// {
// 	t_env *env = malloc(sizeof(t_env));
// 	env->data = ft_strdup("USER");
// 	env->value = ft_strdup("amal42");
// 	env->next = NULL;

// 	char *input = ft_strdup("Hello $USER, welcome!");
// 	char *replaced = replace_in_double(input, &env);
// 	printf("Result: %s\n", replaced);

// 	free(replaced);
// 	free(input);
// 	free(env->data);
// 	free(env->value);
// 	free(env);

// 	return 0;
// }
