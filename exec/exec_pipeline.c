#include "exec.h"
#include "../builtins/builtins.h"
#include <sys/wait.h>

int	g_status = 0;

static void	child_run(t_cmd *c, int i, int pc, int p[][2], s_env **env)
{
	if (i > 0 && dup2(p[i - 1][0], STDIN_FILENO) == -1)
		perror("dup2 in");
	if (i < pc && dup2(p[i][1], STDOUT_FILENO) == -1)
		perror("dup2 out");
	close_all_pipes(pc, p);
	apply_redirs(c);                           /* your <, >, >> function */
	if (c->builtin_id >= 0)
		exit(g_builtins[c->builtin_id].fn(c, env));
	exec_external(c, env, env_list_to_array(*env));
	perror(c->argv[0]);
	exit(127);
}

static void	parent_close_unused(int i, int pc, int p[][2])
{
    (void)pc;
	if (i > 0)
	{
		close(p[i - 1][0]);
		close(p[i - 1][1]);
	}
}

int	exec_pipeline(t_cmd *first, s_env **env)
{
    const int   pc = pipe_count(first);
    int         p[pc][2];
    pid_t       pid;
    int         i;
    int         status;

    if (pc >= 0 && open_all_pipes(pc, p) == -1)
        return (perror("pipe"), 1);
    i = 0;
    while (first)
    {
        pid = fork();
        if (pid == 0)
            child_run(first, i, pc, p, env);
        else if (pid < 0)
            return (perror("fork"), 1);
        parent_close_unused(i, pc, p);
        first = first->next;
        i++;
    }
    close_all_pipes(pc, p);
    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            g_status = WEXITSTATUS(status);
    }
    return (g_status);
}