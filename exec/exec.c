#include "exec.h"
#include "../builtins/builtins.h"

void	exec_external(t_cmd **c, t_env **env, char **envp)
{
	int		i;
	char	**paths;
	char	*path_val;
	char	*try;
	char	*tmp;
	t_env	*node;

    if (!c || !*c || !(*c)->argv || !(*c)->argv[0])
        cleanup_and_exit(env, c, 1);
	if (ft_strchr((*c)->argv[0], '/'))
		execve((*c)->argv[0], (*c)->argv, envp);
	node = find_env_node(*env, "PATH");
	if (node)
		path_val = node->value;
	else
		path_val = "";
	paths = ft_split(path_val, ':');
	if (!paths)
		cleanup_and_exit(env, c, 1);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		try = ft_strjoin(tmp, (*c)->argv[0]);
		free(tmp);
		if (access(try, X_OK) == 0)
			execve(try, (*c)->argv, envp);
		free(try);
		i++;
	}
	execve((*c)->argv[0], (*c)->argv, envp);
	perror((*c)->argv[0]);
	free_strarray(paths);
	free_strarray(envp);
	cleanup_and_exit(env, c, 127);
}

int	exec_single(t_cmd **c, t_env **env)
{
	pid_t	pid;
	int		status;
	char	**envp;

    // For builtins without redirections, execute directly
	if ((*c)->builtin_id >= 0 && (*c)->n_redir == 0)                /* built‑in in parent               */
		return (g_builtins[(*c)->builtin_id].fn(*c, env));
    // For builtins with redirections, fork and apply redirections
    if ((*c)->builtin_id >= 0)
	{
		pid = fork();
		if (pid == 0)
		{
	    	if (apply_redirs(*c) != 0)
    	    	exit(1);
			exit(g_builtins[(*c)->builtin_id].fn(*c, env));
		}
		waitpid(pid, &status, 0);
		// Check if the child process exited normally
		if (WIFEXITED(status))
			// If it did, return the exit status of the child
			return WEXITSTATUS(status);
		else
			return 1;
	}

	envp = env_list_to_array(*env);        /* convert once, reuse in child     */
	if (!envp)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		if (apply_redirs(*c) != 0)
			exit(1);
		exec_external(c, env, envp);
	}
	free_strarray(envp);                   /* parent: we don’t need it anymore  */
	waitpid(pid, &status, 0);
	// Check if the child process exited normally
	if (WIFEXITED(status))
		// If it did, return the exit status of the child
		return WEXITSTATUS(status);
	else
		return 1;
}
