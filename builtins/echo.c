/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:19:29 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:19:30 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../parssing/minishell.h"

static int	is_n_flag(const char *flag)
{
	int	i;

	if (!flag || flag[0] != '-' || flag[1] != 'n')
		return (0);
	i = 1;
	while (flag[i] == 'n')
		i++;
	return (flag[i] == '\0');
}

int	bi_echo(t_cmd *c, t_env **env)
{
	int		i;
	int		nl;

	(void)env;
	i = 1;
	nl = 1;
	while (c->argv[i] && is_n_flag(c->argv[i]))
	{
		nl = 0;
		i++;
	}
	while (c->argv[i])
	{
		ft_putstr_fd(c->argv[i], STDOUT_FILENO);
		i++;
		if (c->argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
