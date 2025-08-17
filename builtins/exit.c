/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:19:43 by ayousr            #+#    #+#             */
/*   Updated: 2025/08/17 23:43:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	bi_exit(t_cmd *c, t_env **env)
{
	int	code;

	code = 0;
	if (c->argv[1])
		code = ft_atoi(c->argv[1]);
	cleanup_and_exit(env, &c, code);
	return (code);
}
