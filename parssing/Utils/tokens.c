/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:50:18 by amsbai            #+#    #+#             */
/*   Updated: 2025/04/21 17:20:50 by amsbai           ###   ########.fr       */
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
			//handle error
			printf("uhhh trallallero trallalla :3\n");
			exit(0);
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
			//handle error
			printf("uhhh trallallero trallalla :3\n");
			exit(0);
		}
		i++;
	}
	(*cmd)->value = ft_substr(str, j, i - j);
	return (i + 1);
}

int	pipes(const char *str, int i, s_tokens **cmd) // For pipe
{
	int	j;

	j = i;
	if(str[i + 1] == '|')
	{
		//handle error
		printf("syntax error !!! (im not required to handle '||')\n");
		exit(0);
	}
	else
	{
		(*cmd)->type = N_PIPE;
		(*cmd)->value = "|";
	}
	return (i + 1);
}

int	redirections1(const char *str, int i, s_tokens **cmd) // For append mode && output
{
	int	j;

	j = i;
	if(str[i + 1] == '>')
	{
		(*cmd)->type = N_APPEND_SIGN;
		(*cmd)->value = ">>";
		i++;
	}
	else
	{
		(*cmd)->type = N_OUTPUT_SIGN;
		(*cmd)->value = ">";
	}
	return (i + 1);
}

int	redirections2(const char *str, int i, s_tokens **cmd) // For delimiter redirection && input
{
	int	j;

	j = i;
	if(str[i + 1] == '<')
	{
		(*cmd)->type = N_APPEND_SIGN;
		(*cmd)->value = "<<";
		i++;
	}
	else
	{
		(*cmd)->type = N_OUTPUT_SIGN;
		(*cmd)->value = "<";
	}
	return (i + 1);
}

void	tokenize_shell(const char* input, s_tokens **cmd)
{
	int	i = 0;
	int	j = 0;
	s_tokens *node;

	while (input[i])
	{
		if (input[i] == '\'')
		{
			node = t_lstnew();
			i = single_quote(input, i + 1, &node); // +1 to skip quote
			t_lstadd_back(cmd,node);
		}
		else if (input[i] == '"')
		{
			node = t_lstnew();
			i = double_quote(input, i + 1, &node); // +1 to skip quote
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
			while(input[i] && input[i] != ' ')
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
//     const char *input = "echo \"hello world\" | grep 'world' > output.txt";
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