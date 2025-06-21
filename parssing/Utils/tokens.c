/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:50:18 by amsbai            #+#    #+#             */
/*   Updated: 2025/06/21 18:24:21 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../builtins/builtins.h"

void	error(char *input, s_tokens **cmd, s_env **listed)
{
	ft_tokensclear(cmd);
	ft_envclear(listed);
	free(input);
}

int	if_envariable(char *str, char **word, char **tmp, s_env **env)
{
	int 	j;
	int		i;
	char	*seg;
	
	i = 0;
	j = i;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '$' || str[i] == '?'))
		i++;
	seg = ft_substr(str, j, i - j);
	seg = replace_in_double(seg, env);
	if (!seg)
	{
		if  (str[i] == '.')
		{
			while(str[i] != ' ')
				i++;
		}
		free(seg);
		seg = ft_strdup("");
	}
	*tmp = ft_strjoin(*word, seg);
	free(*word);
	free(seg);
	*word = *tmp;
	return (i);
}

void	tokenize_shell(char* input, s_tokens **cmd, s_env **listed)
{
	int			i = 0;
	int			j = 0;
	char		*word;
	s_tokens	*node;
	char		*tmp;

	if (!input)
	{
		error(input, cmd, listed);
		return ;
	}
	j = -2;
	while (input[i])
	{
		if(ft_isspace((unsigned char)input[i]))
		{
			i++;
			continue;
		}
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			node = ft_tokenew();
			if (input[i] == '|')
			{
				if (j == -2)
				{
					printf("minishell: syntax error near unexpected token '|'\n");
					g_status = 285;
					error(input, cmd, listed);
					return;
				}
				i =	pipes(input, i, &node);
			}
			else if (input[i] == '<')
				i = redirections2(input, i, &node);
			else if (input[i] == '>')
				i = redirections1(input, i, &node);
			if (i < 0)
			{
				error(input, cmd, listed);
				return ;
			}
			ft_tokenadd_back(cmd,node);
			continue;
		}
		node = ft_tokenew();
		node->type = N_WORD;
		word = ft_strdup("");
		if (!word)
		{
			error(input, cmd, listed);
			exit (0);
		}
		while(input[i] && !ft_isspace(input[i]) && input[i] != '|'
			&& input[i] != '<' && input[i] != '>')
		{
			if (input[i] == '\'')
			{
				j = single_quote(input + i, &word, &tmp);
				if (j < 0)
				{
					printf("minishell: syntax error near unexpected token '\''\n");
					g_status = 1;
					error(input, cmd, listed);
					return ;
				}
				i += j;
			}
			else if (input[i] == '"')
			{
				j = double_quote(input + i, &word, &tmp, listed);
				if (j < 0)
				{
					printf("minishell: syntax error near unexpected token '\"'\n");
					g_status = 1;
					error(input, cmd, listed);
					return ;
				}
				i += j;
			}
			else if (input[i] == '$')
			{
				j = if_envariable(input + i, &word, &tmp, listed);
				i += j;
			}
			else
			{
				j = 0;
				tmp = malloc(ft_strlen(word) + 2);
				if (!tmp)
				{
					ft_tokensclear(cmd);
					ft_envclear(listed);
					free(input);
					exit (0);
				}
				ft_memcpy(tmp, word, ft_strlen(word));
				tmp[ft_strlen(word)] = input[i++];
				tmp[ft_strlen(word) + 1] = '\0';
				free(word);
				word = tmp;
			}
		}
		node->value = word;
		ft_tokenadd_back(cmd, node);
	}
}

// int main()
// {
//     char *input = "ls hh $amal";
//     s_tokens *cmd = NULL;

//     // Allocate memory
//     s_env *hh = malloc(sizeof(s_env));
//     hh->data = ft_strdup("amal");
//     hh->value = ft_strdup("nadya bzf");
//     hh->next = NULL;

//     tokenize_shell(input, &cmd, &hh);

//     s_tokens *curr = cmd;
//     while (curr)
//     {
//         printf("Token Type: %d\tValue: [%s]\n", curr->type, curr->value);
//         curr = curr->next;
//     }

//     return 0;
// }