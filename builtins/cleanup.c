#include "builtins.h"

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*next;
	int		i;

	if (!cmd)  // Check if the pointer to pointer is NULL
		return;
	while (*cmd)  // Check if the actual command pointer is NULL
	{
		next = (*cmd)->next;
		i = 0;
		while ((*cmd)->argv && (*cmd)->argv[i])
			free((*cmd)->argv[i++]);
		free((*cmd)->argv);
		i = 0;
		while (i < (*cmd)->n_redir)
		{
			free((*cmd)->redir[i].filename);
			i++;
		}
		free((*cmd)->redir);
		free(*cmd);  // Free the actual command structure
		*cmd = next;
	}
}

void	cleanup_and_exit(s_env **env, t_cmd **cmd, int n)
{
    free_cmd(cmd);
    ft_envclear(env);
    exit (n);
}
