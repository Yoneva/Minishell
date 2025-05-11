#include "exec.h"

int get_heredoc_fd(const char *limiter)
{
    int   p[2];
    char *line;

    if (pipe(p) == -1)
    {
        perror("pipe");
        return (-1);
    }
    while (1)
    {
        line = readline("heredoc> ");
        if (!line)
        {
            close(p[1]);
            return (p[0]);
        }
        if (strcmp(line, limiter) == 0)
        {
            free(line);
            break;
        }
        write(p[1], line, strlen(line));
        write(p[1], "\n", 1);
        free(line);
    }
    close(p[1]);
    return (p[0]);
}