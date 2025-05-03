#include "builtins.h"

const t_bdispatch g_builtins[] = {
    {"echo",   bi_echo},
    {"cd",     bi_cd},
    {"pwd",    bi_pwd},
    {"export", bi_export},
    {"unset",  bi_unset},
    {"env",    bi_env},
    {"exit",   bi_exit},
    {NULL,     NULL}
};