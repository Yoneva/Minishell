#include "exec.h"
#include "../builtins/builtins.h"
#include <sys/wait.h>

int	g_status = 0;

int	exec_pipeline(t_cmd *first, s_env **env)
{
    int         prev[2];
    int         next[2];
    pid_t       pid;
    int         status;
    int         i;
    t_cmd       *cmd;
    int         is_last;

    cmd = first;
    i = 0;
    while (cmd)
    {
        is_last = (cmd->next == NULL);

        if (!is_last && pipe(next) == -1)
            return (perror("pipe"), 1);
        pid = fork();
        if (pid < 0)
            return (perror("fork"), 1);
        if (pid == 0)
        {
            /* CHILD */
            /* if there was a previous pipe, hook its read end to stdin */
            if (i > 0)
            {
                dup2(prev[0], STDIN_FILENO);
                close(prev[0]);
                close(prev[1]);
            }
            /* if not last, hook next pipe’s write end to stdout */
            if (!is_last)
            {
                dup2(next[1], STDOUT_FILENO);
                close(next[0]);
                close(next[1]);
            }
            /* apply your <, >, >> redirections */
            apply_redirs(cmd);
            /* run builtin or external */
            if (cmd->builtin_id >= 0)
                exit(g_builtins[cmd->builtin_id].fn(cmd, env));
            exec_external(cmd, env, env_list_to_array(*env));
            perror(cmd->argv[0]);
            exit(127);
        }
        /* PARENT */
        if (i > 0)
        {
            close(prev[0]);
            close(prev[1]);            
        }
        if (!is_last)
        {
            close(next[0]);
            close(next[1]);
        }    
        cmd = cmd->next;
        i++;
    }
    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            g_status = WEXITSTATUS(status);
    }
    return (g_status);
}