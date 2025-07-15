/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:19:53 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:29:41 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../parssing/minishell.h"

int	bi_unset(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		unset_env_var(env, cmd->argv[i]);
		i++;
	}
	return (0);
}
