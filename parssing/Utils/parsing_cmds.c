#include "../minishell.h"
#include "../../builtins/builtins.h"

static int  is_redir(int sign)
{
    return (sign == N_INPUT_SIGN || sign == N_OUTPUT_SIGN
            || sign == N_APPEND_SIGN || sign == N_HEREDOC_SIGN);
}

static int count_args(s_tokens *tok)
{
    int count;
    
    count = 0;
    while (tok && tok->type != N_PIPE)
    {
        if (tok->type == N_WORD || tok->type == N_DOUBLE_QUOTE
            || tok->type == N_SINGLE_QUOTE)
            count++;
        tok = tok->next;
    }
    return count;
}

static int count_redirs(s_tokens *tok)
{
    int count;

    count = 0;
    while (tok && tok->type != N_PIPE)
    {
        if (is_redir(tok->type))
            count++;
        tok = tok->next;
    }
    return count;
}

static int builtin_id(const char *word)
{
    int i = 0;

    while (g_builtins[i].name)
    {
        if (!ft_strcmp(word, g_builtins[i].name))
            return (i);
        i++;
    }
    return (-1);
}

static void init_cmd_struct(t_cmd *cmd, int argc, int rcount)
{
    cmd->argv = malloc(sizeof(char *) * (argc + 1));
    cmd->redir = malloc(sizeof(t_redir) * rcount);
    cmd->n_redir = rcount;
    cmd->builtin_id = -1;
    cmd->next = NULL;
}

static void fill_cmd_struct(t_cmd *cmd, s_tokens **tokp)
{
    int args_i;
    int redirs_i;
    s_tokens *tok;

	if (!tokp)
		return ; // to be handled
    tok = *tokp;
    args_i = 0;
    redirs_i = 0;
    while (tok && tok->type != N_PIPE)
    {
        if (tok->type == N_WORD || tok->type == N_DOUBLE_QUOTE
            || tok->type == N_SINGLE_QUOTE)
            cmd->argv[args_i++] = ft_strdup(tok->value);
        else if (is_redir(tok->type))
        {
            if (!tok->next || tok->next->type == N_PIPE)
            {
                return ; // should handle syntax error
            }
            
            cmd->redir[redirs_i].type = tok->type;
            tok = tok->next;
            cmd->redir[redirs_i++].filename = ft_strdup(tok->value);
        }
        tok = tok->next;
    }
    cmd->argv[args_i] = NULL;
    if (cmd->argv[0])
        cmd->builtin_id = builtin_id(cmd->argv[0]);
    
    if (tok && tok->type == N_PIPE)
        tok = tok->next;
    *tokp = tok;
}

static t_cmd *build_one_cmd(s_tokens **tokens)
{
    t_cmd   *cmd;
    int     argc;
    int     rcount;
    
    argc = count_args(*tokens);
    rcount = count_redirs(*tokens);
    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    init_cmd_struct(cmd, argc, rcount);
    fill_cmd_struct(cmd, tokens);
    return (cmd);
}

t_cmd *parse_cmd(s_tokens *tokens)
{
    t_cmd *head;
    t_cmd *prev;
    t_cmd *curr;

    head = NULL;
    prev = NULL;
    while (tokens)
    {
        curr = build_one_cmd(&tokens);
        if (!head)
            head = curr;
        else
            prev->next = curr;
        prev = curr;
    }
	ft_tokensclear(&tokens);
    return (head);
}