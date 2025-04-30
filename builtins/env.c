#include "builtins.h"
#include "../parssing/minishell.h"

int bi_env(t_cmd *cmd, s_env **env)
{
    s_env *node;

    (void)cmd;
    node = *env;
    while (node)
    {
        ft_putstr_fd(node->data, STDOUT_FILENO);
        ft_putchar_fd('=', STDOUT_FILENO);
        ft_putstr_fd(node->value, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        node = node->next;
    }
    return 0;
}