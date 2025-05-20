/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimaneyousr <aimaneyousr@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:50:18 by amsbai            #+#    #+#             */
/*   Updated: 2025/05/19 21:05:20 by aimaneyousr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../builtins/builtins.h"

int	single_quote(const char *str, int i, s_tokens **cmd)
{
	int j;

	j = i;
	(*cmd)->type = N_WORD;
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
	if (!(*cmd)->value)
		return (-1);
	return (i + 1);
}

int	double_quote(const char *str, int i, s_tokens **cmd) // had joj dawyin ela rasehm
{
	int j;

	j = i;
	(*cmd)->type = N_WORD;
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
	i += 1;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			if (str[i] == '|')
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (-1);
			}
			break ;
		}
	}
	(*cmd)->type = N_PIPE;
	(*cmd)->value = ft_strdup("|");
	
	return (i);
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

int	if_envariable(char *input, int i, s_tokens **cmd, s_env **env)
{
	int len;
	char *str;
	s_env *tmp;
	
	tmp = *env;
	len = i;
	i += 1;
	(*cmd)->type = N_WORD;
	while (input[len] && input[len] != ' ')
	{
		len++;
	}
	str = ft_substr((input + i), 0, len);
	while (tmp)
	{
		if(ft_strcmp(str, tmp->data) == 0)
			(*cmd)->value = tmp->value;
		tmp = tmp->next;
	}
	if (env == NULL)
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
		ft_tokensclear(cmd);
		ft_envclear(listed);
		free(input);
		exit (0);
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
				ft_tokensclear(cmd);
				ft_envclear(listed);
				free(input);
				exit (0);
			}
			ft_tokenadd_back(cmd,node);
			continue;
		}
		node = ft_tokenew();
		node->type = N_WORD;
		word = strdup("");
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