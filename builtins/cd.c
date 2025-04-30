#include "builtins.h"
#include "../parssing/minishell.h"

int bi_cd(t_cmd *cmd, s_env **env)
{
    char *target;
    char *oldpwd;
    char *newpwd;

    oldpwd = getcwd(NULL, 0);
    if (!cmd->argv[1] || !cmd->argv[1][0])
        target = getenv("HOME");
    else if (!ft_strcmp(cmd->argv[1], target))
        target = getenv("OLDPWD");
    else
        target = cmd->argv[1];
    if (!target || chdir(target) < 0)
    {
        perror("cd");
        free(oldpwd);
        return (1);
    }
    newpwd = getcwd(NULL, 0);
    set_env_var(env, "OLDPWD", oldpwd);
    set_env_var(env, "PWD", newpwd);
    free(oldpwd);
    free(newpwd);
    return (0);
}
