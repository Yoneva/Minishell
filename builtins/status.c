#include "../parssing/minishell.h"

static int g_status = 0;

int get_status(void)
{
    return (g_status);
}

void set_status(int status)
{
    g_status = status;
}