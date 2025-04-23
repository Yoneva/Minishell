#include "exec.h"
#include "../parssing/minishell.h"
#include <sys/wait.h>

int	exec_single(t_cmd *c, s_env **env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	if (c->builtin_id >= 0)                /* built‑in in parent               */
		return (g_builtins[c->builtin_id].fn(c, env));
	envp = env_list_to_array(*env);        /* convert once, reuse in child     */
	if (!envp)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		execve(c->argv[0], c->argv, envp); /* never returns on success          */
		perror("execve");
		free_strarray(envp);
		exit(127);
	}
	free_strarray(envp);                   /* parent: we don’t need it anymore  */
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}

