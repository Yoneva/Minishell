/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:50:18 by amsbai            #+#    #+#             */
/*   Updated: 2025/05/20 13:48:33 by amsbai           ###   ########.fr       */
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

int	if_envariable(char *input, int i, s_tokens **cmd, s_env **env)
{
	int len;
	s_env *tmp;
	
	tmp = *env;
	len = i;
	i += 1;
	while (input[len] && input[len] != ' ')
	{
		len++;
	}
	(*cmd)->type = N_WORD;
	(*cmd)->value = serachforvar(input + i, env);
	if ((*cmd)->value == NULL)
		return (-1);
	return (len);
}

void	tokenize_shell(char* input, s_tokens **cmd, s_env **listed)
{
	int			i = 0;
	int			j = 0;
	char		*word;
	s_tokens	*node;
	s_env		*env_node;
	char		*seg;
	char		*tmp;
	char		*name;
	const char	*value;

	if (!input)
	{
		error(input, cmd, listed);
		return ;
	}
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
				i = pipes(input, i, &node);
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
			ft_tokensclear(cmd);
			ft_envclear(listed);
			free(input);
			exit (0);
		}
		while(input[i] && !ft_isspace(input[i]) && input[i] != '|'
			&& input[i] != '<' && input[i] != '>')
		{
			if (input[i] == '\'')
			{
				i++;
				j = i;
				while (input[i] && input[i] != '\'')
					i++;
				if (!input[i])
				{
					perror("single quote");
					ft_tokensclear(cmd);
					ft_envclear(listed);
					free(input);
					exit (0);
				}
				seg = substr_quotes(input, j, i - j, 0);
				tmp = ft_strjoin(word, seg);
				free(word);
				free(seg);
				word = tmp;
				i++;		
			}
			else if (input[i] == '"')
			{
				i++;
				j = i;
				while (input[i] && input[i] != '"')
					i++;
				if (!input[i])
				{
					perror("double quote");
					ft_tokensclear(cmd);
					ft_envclear(listed);
					free(input);
					exit (0);
				}
				seg = substr_quotes(input, j, i - j, 0);
				tmp = ft_strjoin(word, seg);
				free(word);
				free(seg);
				word = tmp;
				i++;
			}
			else if (input[i] == '$')
			{
				i++;
				j = i;
				while (input[i] && (ft_isalnum(input[i])
						|| input[i] == '_'))
					i++;
				name = ft_substr(input, j, i - j);
				env_node = find_env_node(*listed, name);
				if (env_node)
					value = env_node->value;
				else
					value = "";
				tmp = ft_strjoin(word, value);
				free(word);
				free(name);
				word = tmp;
			}
			else
			{
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