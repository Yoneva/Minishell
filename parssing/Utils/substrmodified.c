/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substrmodified.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:57:21 by amsbai            #+#    #+#             */
/*   Updated: 2025/06/24 21:07:36 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*substr_quotes(char const *s, unsigned int start, size_t len, size_t i)
{
	char	*str;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	i = 0;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
 	{
 		if (s[start] == '\'' || s[start] == '"')
 		{
 			start++;
			len--;  // Decrease len to account for the skipped quote
 			continue;
 		}
 		str[i] = s[start];
 		i++;
 		start++;
 	}
	str[i] = '\0';
	return (str);
}
