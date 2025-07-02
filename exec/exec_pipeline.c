#include "exec.h"
#include "../builtins/builtins.h"
#include <sys/wait.h>

int	g_status = 0;

static void setup_child_pipes(int prev[2], int next[2], int i, int it_last)
{
    if (i > 0 && prev[0] >= 0)
    {
        dup2(prev[0], STDIN_FILENO);
        close(prev[0]);
        close(prev[1]);
    }
    if (!it_last && next[1] >= 0)
    {
        dup2(next[1], STDOUT_FILENO);
        close(next[0]);
        close(next[1]);
    }
}

static void execute_command(t_cmd **cmd, t_env **env)
{
    apply_redirs(*cmd);
    if ((*cmd)->builtin_id >= 0)
        exit(g_builtins[(*cmd)->builtin_id].fn(*cmd, env));
    
    char **envp = env_list_to_array(*env);
    exec_external(cmd, env, envp);
    exit(127);
}

static void close_parent_pipes(int prev[2], int next[2], int i, int it_last)
{
    if (i > 0)
    {
        close(prev[0]);
        close(prev[1]);
    }
    if (!it_last)
    {
        prev[0] = next[0];  // Close read end in parent
        prev[1] = next[1];  // Close write end in parent
    }
}

static int create_process(t_cmd *cmd, int next[2])
{
    pid_t pid;
    int it_last;
    
    it_last = (cmd->next == NULL);
    if (!it_last && pipe(next) == -1)
        return (perror("pipe"), -1);
    
    pid = fork();
    if (pid < 0)
        return (perror("fork"), -1);
    return pid;
}

int	exec_pipeline(t_cmd *first, t_env **env)
{
    int prev[2], next[2], status, i;
    pid_t pid;
    t_cmd *cmd;
    
    cmd = first;
    i = 0;
    while (cmd)
    {
        pid = create_process(cmd, next);
        if (pid == -1)
            return 1;
        
        if (pid == 0)
        {
            setup_child_pipes(prev, next, i, cmd->next == NULL);
            execute_command(&cmd, env);
        }
        
        close_parent_pipes(prev, next, i, cmd->next == NULL);
        if (cmd->next)
            ft_memcpy(prev, next, sizeof(prev));
        
        cmd = cmd->next;
        i++;
    }
    
    while (wait(&status) > 0)
        if (WIFEXITED(status))
            g_status = WEXITSTATUS(status);
    
    return (g_status);
}
