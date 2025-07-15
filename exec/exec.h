/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:45:26 by ayousr            #+#    #+#             */
/*   Updated: 2025/07/15 02:45:27 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../parssing/minishell.h"
# include <sys/wait.h>
# include <fcntl.h>

void	exec_external(t_cmd *c, t_env **env, char **envp);
char	**env_list_to_array(t_env *lst);
int		apply_redirs(t_cmd *c);
void	free_strarray(char **arr);
int		pipe_count(t_cmd *c);
int		open_all_pipes(int n, int p[][2]);
void	close_all_pipes(int n, int p[][2]);
int		get_heredoc_fd(const char *limiter);

#endif
