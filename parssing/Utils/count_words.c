/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 21:20:16 by amsbai            #+#    #+#             */
/*   Updated: 2025/04/18 19:14:19 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*freeing(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char **count_malloc(const char *str)
{
	int i = 0, count = 0;
	int in_squote = 0, in_dquote = 0;

	while (str[i])
	{
		// Skip whitespace
		while (!in_squote && !in_dquote && is_whitespace(str[i]))
			i++;

		if (!str[i])
			break;

		count++;

		// If it's an operator outside quotes, skip it (handle >> and << too)
		if (!in_squote && !in_dquote && is_operator_char(str[i]))
		{
			if ((str[i] == '>' || str[i] == '<') && str[i + 1] == str[i])
				i++;
			i++;
			continue;
		}

		// Parse a word or quoted token
		while (str[i])
		{
			if (str[i] == '\'' && !in_dquote)
				in_squote = !in_squote;
			else if (str[i] == '"' && !in_squote)
				in_dquote = !in_dquote;
			else if (!in_squote && !in_dquote &&
				(is_whitespace(str[i]) || is_operator_char(str[i])))
				break;
			i++;
		}
	}

	printf("%d\n", count);
	char **arr = malloc((count + 1) * sizeof(char *));
	if (arr)
		arr[count] = NULL;
	return arr;
}


// int main()
// {
// 	const char* command = "echo \"Hello world\" | grep world > output.txt";

// 	char **aa = count_malloc(command);

// 	return 0;
// }
