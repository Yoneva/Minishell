/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:19:19 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:37:04 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

const t_bdispatch	g_builtins[] = {
{"echo", bi_echo},
{"cd", bi_cd},
{"pwd", bi_pwd},
{"export", bi_export},
{"unset", bi_unset},
{"env", bi_env},
{"exit", bi_exit},
{NULL, NULL}
};