/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:19:23 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:35:38 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../parssing/minishell.h"

static char	*get_cd_target(char **argv)
{
	if (!argv[1] || !argv[1][0])
		return (getenv("HOME"));
	if (!ft_strcmp(argv[1], "OLDPWD"))
		return (getenv("OLDPWD"));
	return (argv[1]);
}

int	bi_cd(t_cmd *cmd, t_env **env)
{
	char	*target;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	target = get_cd_target(cmd->argv);
	if (!target || chdir(target) < 0)
	{
		perror("cd");
		if (oldpwd)
			free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (oldpwd)
	{
		set_env_var(env, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	if (newpwd)
	{
		set_env_var(env, "PWD", newpwd);
		free(newpwd);
	}
	return (0);
}
