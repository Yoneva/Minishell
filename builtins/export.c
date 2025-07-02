#include "builtins.h"
#include "../parssing/minishell.h"

int   bi_export(t_cmd *c, t_env **env)
{
    int     i;
    char    *eq;
    int     count;
    t_env   **env_array = NULL;
    t_env   *node;

    i = 1;
    if (!c->argv[i])
    {
        count = count_env_vars(*env);
        env_array = malloc(sizeof(t_env*) * count);
        if (!env_array)
        {
            perror("export: malloc");
            return 1;
        }
        // fill the array
        node = *env;
        i = 0;
        while (node)
        {
            env_array[i++] = node;
            node = node->next;
        }
        sort_env_vars(env_array, count);
        i = 0;
        while (i < count)
        {
            ft_putstr_fd("declare -x ", STDOUT_FILENO);
            ft_putstr_fd(env_array[i]->data, STDOUT_FILENO);
            ft_putstr_fd("=\"", STDOUT_FILENO);
            ft_putstr_fd(env_array[i]->value, STDOUT_FILENO);
            ft_putstr_fd("\"\n", STDOUT_FILENO);
            i++;
        }
        free(env_array);
        return (0);
    }
    i = 1;
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