#include "builtins.h"

int	bi_exit(t_cmd *c, s_env **env)
{
    int code;

    (void)env;
    code = 0;
    if (c->argv[1])
        code = ft_atoi(c->argv[1]);
    // rl_clear_history ();
	cleanup_and_exit(env, &c, code);
    return (code);
}