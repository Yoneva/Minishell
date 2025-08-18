/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:19:19 by ayousr            #+#    #+#             */
/*   Updated: 2025/08/18 02:36:18 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

const t_builtin	*get_builtins(void)
{
	static const t_builtin	g_builtins[] = {
	{"echo", bi_echo},
	{"cd", bi_cd},
	{"pwd", bi_pwd},
	{"export", bi_export},
	{"unset", bi_unset},
	{"env", bi_env},
	{"exit", bi_exit},
	{NULL, NULL}
	};

	return (g_builtins);
}
