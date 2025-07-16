/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:19:43 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 19:14:04 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	bi_exit(t_cmd *c, t_env **env)
{
	int	code;

	code = 0;
	//check if the given number to exit exceeds long long
	// then
	//check if there is more than one arg + 
	if (c->argv[1])
		code = ft_atoi(c->argv[1]);
	cleanup_and_exit(env, &c, code);
	return (code);
}
