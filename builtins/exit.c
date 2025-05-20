#include "builtins.h"

int	bi_exit(t_cmd *c, s_env **env)
{
    int code;

    code = 0;
    if (c->argv[1])
        code = ft_atoi(c->argv[1]);
	cleanup_and_exit(env, &c, code);
    return (code);
}