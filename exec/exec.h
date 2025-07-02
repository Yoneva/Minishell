#ifndef EXEC_H
# define EXEC_H

# include "../parssing/minishell.h"
# include <sys/wait.h>
# include <fcntl.h>

void	exec_external(t_cmd **c, t_env **env, char **envp);
char	**env_list_to_array(t_env *lst);
int		apply_redirs(t_cmd *c);
void	free_strarray(char **arr);
int   pipe_count(t_cmd *c);
int   open_all_pipes(int n, int p[][2]);
void	close_all_pipes(int n, int p[][2]);
int   get_heredoc_fd(const char *limiter);

#endif /* EXEC_H */
