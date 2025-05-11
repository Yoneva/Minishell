#include "exec.h"
#include "../builtins/builtins.h"

int	apply_redirs(t_cmd *c)
{
    int fd;
    int target_fd;
    int i;

    i = 0;
    while (i < c->n_redir)
    {
        if (c->redir[i].type == N_HEREDOC_SIGN)
            fd = get_heredoc_fd(c->redir[i].filename);
        else if (c->redir[i].type == N_OUTPUT_SIGN)
            fd = open(c->redir[i].filename, O_CREAT | O_TRUNC | O_WRONLY | 0644);
        else if (c->redir[i].type == N_APPEND_SIGN)
            fd = open(c->redir[i].filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
        else if (c->redir[i].type == N_INPUT_SIGN)
            fd = open(c->redir[i].filename, O_RDONLY);
        else
            fd = -1;
        if (c->redir[i].type == N_INPUT_SIGN
            || c->redir[i].type == N_HEREDOC_SIGN)
            target_fd = STDIN_FILENO;
        else
            target_fd = STDOUT_FILENO;
        if (fd < 0 || dup2(fd, target_fd) < 0)
        {
            perror(c->redir[i].filename);
            if (fd >= 0)
                close(fd);
            return (1);
        }
        close(fd);
        i++;
    }
	return (0);
}
