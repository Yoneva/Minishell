#include "builtins.h"
#include "../parssing/minishell.h"

int	bi_exit(t_cmd *c, s_env **env)
{
    int code;

    (void)env;
    code = 0;
    if (c->argv[1])
        code = ft_atoi(c->argv[1]);
	cleanup_and_exit(env,(*env)->tmp, &c, code);
    return (code);
}