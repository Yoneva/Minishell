#include "builtins.h"
#include "../exec/exec.h"
#include "../parssing/minishell.h"

s_env    *g_env_list = NULL;
s_tokens *g_tokens = NULL;
t_cmd    *g_cmds = NULL;

void free_env_list(s_env *env)
{
    s_env *next;

    while (env)
    {
        next = env->next;
        free(env->data);
        free(env->value);
        free(env);
        env = next;
    }
}

void free_tokens(s_tokens *tok)
{
    s_tokens *next;
    while (tok)
    {
        next = tok->next;
        free(tok->value);
        free(tok);
        tok = next;
    }
}

void free_cmd(t_cmd *cmd)
{
    t_cmd   *next;
    int     i;

    while (cmd)
    {
        next = cmd->next;
        i = 0;
        while (cmd->argv && cmd->argv[i])
            free(cmd->argv[i++]);
        free(cmd->argv);
        i = 0;
        while (i < cmd->n_redir)
        {
            free(cmd->redir[i].filename);
            i++;
        }
        free(cmd->redir);
        free(cmd);
        cmd = next;
    }
}

void cleanup_and_exit(int code)
{
    free_cmd(g_cmds);
    free_tokens(g_tokens);
    free_env_list(g_env_list);
    exit(code);
}