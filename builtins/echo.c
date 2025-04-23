#include "builtins.h"
#include "../parssing/minishell.h"

int	bi_echo(t_cmd *c, s_env **env)
{
	int		i;
	int		nl;

	(void)env;
	i = 1;
	nl = 1;
	if (c->argv[1] && !ft_strcmp(c->argv[1], "-n"))
	{
		nl = 0;
		while (c->argv[i] && !ft_strcmp(c->argv[i], "-n"))
			i++;
	}
	// Iterate through arguments and append a space between them for proper formatting
	while (c->argv[i])
	{
		ft_putstr_fd(c->argv[i], STDOUT_FILENO);
		if (c->argv[++i]) // Increment index and check if there's another argument
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (nl != 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	// Return 0 to indicate successful execution of the echo command
	return (0);
}
