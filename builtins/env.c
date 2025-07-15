/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:19:36 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:28:14 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../parssing/minishell.h"

int	bi_env(t_cmd *cmd, t_env **env)
{
	t_env	*node;

	(void)cmd;
	node = *env;
	while (node)
	{
		ft_putstr_fd(node->data, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(node->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		node = node->next;
	}
	return (0);
}
