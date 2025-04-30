#include "builtins.h"
#include "../parssing/minishell.h"

int   bi_export(t_cmd *c, s_env **env)
{
    int     i;
    char    *eq;

    i = 1;
    if (!c->argv[i])
    {
        s_env *node = *env;
        while (node)
        {
            printf("%s=%s\n", node->data, node->value);
            node = node->next;
        }
        return (0);
    }
    while (c->argv[i])
    {
        eq = ft_strchr(c->argv[i], '=');
        if (eq)
        {
            *eq = '\0';
            set_env_var(env, c->argv[i], eq + 1);
            *eq = '=';
        }
        else
            set_env_var(env, c->argv[i], "");
        i++;
    }
    return (0);
}