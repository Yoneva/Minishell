#include "builtins.h"
#include "../parssing/minishell.h"

void sort_env_vars(s_env **env_array, int count)
{
    int     i;
    int     j;
    s_env   *temp;

    i = 0;
    while (i < count - 1)
    {
        j = 0;
        while (j < count - i - 1)
        {
            if (ft_strcmp(env_array[j]->data, env_array[j + 1]->data) > 0)
            {
                temp = env_array[j];
                env_array[j] = env_array[j + 1];
                env_array[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

int count_env_vars(s_env *env)
{
    int count;

    count = 0;
    s_env *node = env;
    while (node)
    {
        count++;
        node = node->next;
    }
    return count;
    
}

s_env *find_env_node(s_env *env, const char *key)
{
    while (env)
    {
        if (!ft_strcmp(env->data, key))
            return (env);
        env = env->next;
    }
    return (NULL);
}

void set_env_var(s_env **env, const char *k, const char *v)
{
    s_env *node;

    node = find_env_node(*env, k);
    if (node)
    {
        free(node->value);
        node->value = ft_strdup(v);
    }
    else
    {
        s_env *new = ft_envnew();
        new->data = ft_strdup(k);
        new->value = ft_strdup(v);
        ft_envadd_back(env, new);
    }
}

void unset_env_var(s_env **env, const char *key)
{
    s_env *prev = NULL;
    s_env *curr = *env;

    while (curr)
    {
        if (!ft_strcmp(curr->data, key))
        {
            if (prev)
                prev->next = curr->next;
            else
                *env = curr->next;
            free(curr->data);
            free(curr->value);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}
