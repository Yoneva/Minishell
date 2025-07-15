/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:45:33 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 19:03:21 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

extern int	g_status;

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	rl_clear_history();
	rl_cleanup_after_signal();
	write(1, "\n", 1);
	rl_on_new_line();
	exit(130);
}

static int	heredoc_loop(int write_fd, const char *limiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			return (0);
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			return (0);
		}
		if (write(write_fd, line, ft_strlen(line)) == -1 || \
			write(write_fd, "\n", 1) == -1)
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

static void	heredoc_child(int *p, const char *limiter)
{
	int	exit_status;

	signal(SIGINT, heredoc_sigint_handler);
	close(p[0]);
	exit_status = heredoc_loop(p[1], limiter);
	close(p[1]);
	exit(exit_status);
}

static int	wait_for_heredoc(pid_t pid, int *p, void (*old_sigint)(int))
{
	int	status;

	close(p[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, old_sigint);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_status = 130;
		close(p[0]);
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(p[0]);
		return (-1);
	}
	return (p[0]);
}

int	get_heredoc_fd(const char *limiter)
{
	int		p[2];
	pid_t	pid;
	void	(*old_sigint)(int);

	if (pipe(p) == -1)
	{
		perror("pipe");
		return (-1);
	}
	old_sigint = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(p[0]);
		close(p[1]);
		signal(SIGINT, old_sigint);
		return (-1);
	}
	if (pid == 0)
		heredoc_child(p, limiter);
	return (wait_for_heredoc(pid, p, old_sigint));
}
