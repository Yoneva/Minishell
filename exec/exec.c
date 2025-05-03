#include "exec.h"
#include "../builtins/builtins.h"
#include "../parssing/minishell.h"
#include <sys/wait.h>

static void exec_external(t_cmd *c, s_env **env, char **envp)
{
	int		i;
	char	**paths;
	char	*path_val;
	char	*try;
	char	*tmp;
	s_env	*node;

	if (ft_strchr(c->argv[0], '/'))
		execve(c->argv[0], c->argv, envp);
	node = find_env_node(*env, "PATH");
	if (node)
		path_val = node->value;
	else
		path_val = "";
	paths = ft_split(path_val, ':');
	if (!paths)
		cleanup_and_exit(1);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		try = ft_strjoin(tmp, c->argv[0]);
		free(tmp);
		if (access(try, X_OK) == 0)
			execve(try, c->argv, envp);
		free(try);
		i++;
	}
	execve(c->argv[0], c->argv, envp);
	perror(c->argv[0]);
	free_strarray(envp);
	cleanup_and_exit(127);
}

int	exec_single(t_cmd *c, s_env **env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	if (c->builtin_id >= 0 && c->n_redir == 0)                /* built‑in in parent               */
		return (g_builtins[c->builtin_id].fn(c, env));
	envp = env_list_to_array(*env);        /* convert once, reuse in child     */
	if (!envp)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (apply_redirs(c))
			cleanup_and_exit(1);
		if (c->builtin_id >= 0)
			cleanup_and_exit(g_builtins[c->builtin_id].fn(c, env));
		exec_external(c, env, envp);
	}
	free_strarray(envp);                   /* parent: we don’t need it anymore  */
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}

