/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:50:18 by amsbai            #+#    #+#             */
/*   Updated: 2025/05/03 13:41:17 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	single_quote(const char *str, int i, s_tokens **cmd)
{
	int j;

	j = i;
	(*cmd)->type = N_SINGLE_QUOTE;
	while(str[i])
	{
		if(str[i] == '\'')
			break ;
		else if(str[i + 1] == 0 && str[i] != '\'')
		{
			return (-1);
		}
		i++;
	}
	(*cmd)->value = ft_substr(str, j, i - j);
	return (i + 1);
}

int	double_quote(const char *str, int i, s_tokens **cmd) // had joj dawyin ela rasehm
{
	int j;

	j = i;
	(*cmd)->type = N_DOUBLE_QUOTE;
	while(str[i])
	{
		if(str[i] == '"')
			break ;
		else if(str[i + 1] == 0 && str[i] != '\'')
		{
			return (-1);
		}
		i++;
	}
	(*cmd)->value = ft_substr(str, j, i - j);
	return (i + 1);
}

int	pipes(const char *str, int i, s_tokens **cmd) // For pipe
{
	if(str[i + 1] == '|')
	{
		return (-1);
	}
	else
	{
		(*cmd)->type = N_PIPE;
		(*cmd)->value = ft_strdup("|");
	}
	return (i + 1);
}

int	redirections1(const char *str, int i, s_tokens **cmd) // For append mode && output
{
	if(str[i + 1] == '>')
	{
		(*cmd)->type = N_APPEND_SIGN;
		(*cmd)->value = ft_strdup(">>");
		i++;
	}
	else
	{
		(*cmd)->type = N_OUTPUT_SIGN;
		(*cmd)->value = ft_strdup(">");
	}
	return (i + 1);
}

int	redirections2(const char *str, int i, s_tokens **cmd) // For delimiter redirection && input
{
	if(str[i + 1] == '<')
	{
		(*cmd)->type = N_HEREDOC_SIGN;
		(*cmd)->value = ft_strdup("<<");
		i++;
	}
	else
	{
		(*cmd)->type = N_INPUT_SIGN;
		(*cmd)->value = ft_strdup("<");
	}
	return (i + 1);
}

void	tokenize_shell(char* input, s_tokens **cmd)
{
	int	i = 0;
	int	j = 0;
	s_tokens *node;

	if (!input)
		return ;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			node = t_lstnew();
			i = single_quote(input, i + 1, &node); // +1 to skip quote
			if(i == -1)
			{
				t_lstclear(cmd);
				free(input);
			}
			t_lstadd_back(cmd,node);
		}
		else if (input[i] == '"')
		{
			node = t_lstnew();
			i = double_quote(input, i + 1, &node); // +1 to skip quote
			if(i == -1)
			{
				t_lstclear(cmd);
				free(input);
			}
			t_lstadd_back(cmd,node);
		}
		else if (input[i] == '|')
		{
			node = t_lstnew();
			i = pipes(input, i, &node);
			t_lstadd_back(cmd,node);
		}
		else if (input[i] == '<')
		{
			node = t_lstnew();
			i = redirections2(input, i, &node);
			t_lstadd_back(cmd,node);
		}
		else if (input[i] == '>')
		{
			node = t_lstnew();
			i = redirections1(input, i, &node);
			t_lstadd_back(cmd,node);
		}
		else if(input[i] == ' ')
		{
			i++;
			continue;
		}
		else
		{
			node = t_lstnew();
			j = i;
			while(input[i] && (input[i] != ' ' || input[i] != '\t'))
			{
				i++;
			}
			node->type = N_WORD;
			node->value = ft_substr(input, j, i - j);
			t_lstadd_back(cmd,node);
		}
	}
}

// int main()
// {
//     char *input = "ls";
//     s_tokens *cmd = NULL;

//     tokenize_shell(input, &cmd);
//     s_tokens *curr = cmd;
//     while (curr)
//     {
//         printf("Token Type: %d\tValue: [%s]\n", curr->type, curr->value);
//         curr = curr->next;
//     }
//     return 0;
// }