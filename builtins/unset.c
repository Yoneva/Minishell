#include "builtins.h"
#include "../parssing/minishell.h"

int bi_unset(t_cmd *cmd, t_env **env)
{
    int i;

    i = 1;
    while (cmd->argv[i])
    {
        unset_env_var(env, cmd->argv[i]);
        i++;
    }
    return (0);
}