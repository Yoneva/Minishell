#include "builtins.h"
#include "../parssing/minishell.h"

static int is_n_flag(const char *flag)
{
	int i;

	if (!flag || flag[0] != '-' || flag[1] != 'n')
		return (0);
	i = 1;
	while (flag[i] == 'n')
		i++;
	return (flag[i] == '\0');
	
}
int	bi_echo(t_cmd *c, s_env **env)
{
	int		i;
	int		nl;

	(void)env;
	i = 1;
	nl = 1;
	while (c->argv[i] && is_n_flag(c->argv[i]))
	{
		nl = 0;
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
