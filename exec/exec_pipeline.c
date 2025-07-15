/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:44:13 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:52:35 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../builtins/builtins.h"
#include <sys/wait.h>

static void	setup_child_pipes(int p[2][2], int i, int is_last)
{
	if (i > 0)
	{
		dup2(p[(i + 1) % 2][0], STDIN_FILENO);
		close(p[(i + 1) % 2][0]);
		close(p[(i + 1) % 2][1]);
	}
	if (!is_last)
	{
		dup2(p[i % 2][1], STDOUT_FILENO);
		close(p[i % 2][0]);
		close(p[i % 2][1]);
	}
}

static void	execute_piped_command(t_cmd *cmd, t_env **env)
{
	char	**envp;

	if (apply_redirs(cmd) != 0)
	{
		if (g_status == 130)
			exit(130);
		else
			exit(1);
	}
	if (cmd->builtin_id >= 0)
		exit(g_builtins[cmd->builtin_id].fn(cmd, env));
	envp = env_list_to_array(*env);
	exec_external(cmd, env, envp);
	exit(127);
}

static int	wait_for_pipeline(void)
{
	int	status;
	int	last_status;

	last_status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
	}
	return (last_status);
}

static void	run_pipeline(t_cmd *cmd, t_env **env, int p[2][2])
{
	int		i;
	pid_t	pid;

	i = 0;
	while (cmd)
	{
		if (cmd->next && pipe(p[i % 2]) == -1)
			exit(1);
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			setup_child_pipes(p, i, cmd->next == NULL);
			execute_piped_command(cmd, env);
		}
		if (i > 0)
		{
			close(p[(i + 1) % 2][0]);
			close(p[(i + 1) % 2][1]);
		}
		cmd = cmd->next;
		i++;
	}
}

int	exec_pipeline(t_cmd *first, t_env **env)
{
	int	p[2][2];

	run_pipeline(first, env, p);
	return (wait_for_pipeline());
}
