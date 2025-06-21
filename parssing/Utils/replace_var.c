/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:42:42 by amsbai            #+#    #+#             */
/*   Updated: 2025/06/21 17:45:40 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_in_double(char *input, s_env **env)
{
	char	*result; // Initialize empty result string
	char	*tmp;
	int		i;
	int		j;
	
	result = ft_strdup(""); 
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')          // Found variable start
		{
			i += 1;
			j = i;
			tmp = serachforvar(input + i, env); // Search for variable in env list
			// g_status = 0;
			if (tmp)
				result = ft_strjoin(result, tmp); // Add value to result
			else
				return NULL;
			while (input[i] && (ft_isalnum(input[i]) || input[i] == '_' || input[j] == '?'))
				i++;  // skip variable name
		}
		else if(input[i] == '"')
			break ;
		else // Regular character
		{
			char *s = malloc(2);
			if (!s)
				return NULL;
			s[0] = input[i];
			s[1] = '\0';
			result = ft_strjoin(result, s);  // add char to result
			free(s);
			i++;
		}
	}
	return (result);
}

// int main()
// {
// 	s_env *env = malloc(sizeof(s_env));
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
