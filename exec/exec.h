#ifndef EXEC_H
# define EXEC_H

# include "../parssing/minishell.h"
# include <sys/wait.h>
# include <fcntl.h>

void	exec_external(t_cmd **c, s_env **env, char **envp, s_tokens **tokens);
char	**env_list_to_array(s_env *lst);
int		apply_redirs(t_cmd *c);
void	free_strarray(char **arr);

#endif /* EXEC_H */
