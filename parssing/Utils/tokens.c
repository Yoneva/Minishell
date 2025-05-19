/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:50:18 by amsbai            #+#    #+#             */
/*   Updated: 2025/05/19 16:15:37 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int	i = 0;
	int	j = 0;
	s_tokens *node;

	if (!input)
	{
		error(input, cmd, listed);
		return ;
	}
	while (input[i])
	{
		if (input[i] == '\'')
		{
			node = ft_tokenew();
			i = single_quote(input, i + 1, &node); // +1 to skip quote
			if(i == -1)
			{
				error(input, cmd, listed);
				return ;
			}
			ft_tokenadd_back(cmd,node);
		}
		else if (input[i] == '"')
		{
			node = ft_tokenew();
			i = double_quote(input + i, i + 1, &node, listed); // +1 to skip quote
			if(i == -1)
			{
				error(input, cmd, listed);
				return ;
			}
			ft_tokenadd_back(cmd,node);
		}
		else if (input[i] == '|')
		{
			node = ft_tokenew();
			i = pipes(input, i, &node);
			if(i == -1)
			{
				error(input, cmd, listed);
				return ;
			}
			ft_tokenadd_back(cmd,node);
		}
		else if (input[i] == '<')
		{
			node = ft_tokenew();
			i = redirections2(input, i, &node);
			if(i == -1)
			{
				error(input, cmd, listed);
				return ;
			}
			ft_tokenadd_back(cmd,node);
		}
		else if (input[i] == '>')
		{
			node = ft_tokenew();
			i = redirections1(input, i, &node);
			if(i == -1)
			{
				error(input, cmd, listed);
				return ;
			}
			ft_tokenadd_back(cmd,node);
		}
		else if (input[i] == '$')
		{
			node = ft_tokenew();
			i = if_envariable(input, i, &node, listed);
			if(i == -1)
			{
				error(input, cmd, listed);
				return ;
			}
			ft_tokenadd_back(cmd,node);
		}
		else if(input[i] == ' ')
		{
			i++;
			continue;
		}
		else
		{
			node = ft_tokenew();
			j = i;
			while(input[i] && (input[i] != ' ' && input[i] != '\t'))
			{
				i++;
			}
			node->type = N_WORD;
			node->value = substr_quotes(input, j, i - j, 0);
			ft_tokenadd_back(cmd,node);
		}
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