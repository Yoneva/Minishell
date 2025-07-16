/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:45:24 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:52:11 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../builtins/builtins.h"
#include "../builtins/status.h"

static void	try_paths(char **argv, t_env *env, char **envp)
{
	char	**paths;
	char	*path_val;
	char	*try_path;
	char	*tmp;
	int		i;

	path_val = "";
	if (find_env_node(env, "PATH"))
		path_val = find_env_node(env, "PATH")->value;
	paths = ft_split(path_val, ':');
	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		try_path = ft_strjoin(tmp, argv[0]);
		free(tmp);
		if (access(try_path, X_OK) == 0)
			execve(try_path, argv, envp);
		free(try_path);
		i++;
	}
	free_strarray(paths);
}

void	exec_external(t_cmd *c, t_env **env, char **envp)
{
	if (!c || !c->argv || !c->argv[0])
		cleanup_and_exit(env, &c, 1);
	if (ft_strchr(c->argv[0], '/'))
		execve(c->argv[0], c->argv, envp);
	try_paths(c->argv, *env, envp);
	execve(c->argv[0], c->argv, envp);
	perror(c->argv[0]);
	free_strarray(envp);
	cleanup_and_exit(env, &c, 127);
}

static int	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static int	exec_forked(t_cmd *c, t_env **env)
{
	pid_t	pid;
	char	**envp;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (apply_redirs(c) != 0)
		{
			if (get_status() == 130)
				exit(130);
			else
				exit(1);
		}
		if (c->builtin_id >= 0)
			exit(get_builtins()[c->builtin_id].fn(c, env));
		envp = env_list_to_array(*env);
		exec_external(c, env, envp);
	}
	return (wait_for_child(pid));
}

int	exec_single(t_cmd *c, t_env **env)
{
	if (c->builtin_id >= 0 && c->n_redir == 0)
		return (get_builtins()[c->builtin_id].fn(c, env));
	return (exec_forked(c, env));
}
