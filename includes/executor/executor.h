/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:35:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/14 07:24:59 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <sys/stat.h>

# include "global.h"
# include "parser/parser.h"
# include "expander/expander.h"
# include "builtin/builtin.h"
# include "utils/exit_status.h"
# include "utils/environment.h"
# include "utils/signal_handler.h"

# define READ	0
# define WRITE	1

# define NOT_BUILTIN -1

// executor.c
int		execute(t_list *commands, bool is_subshell);
int		execute_wait_pid(int last_pid);
int		execute_wait_pid_all(int last_pid);

// group.c
int		execute_group(t_list *commands);

// pipeline.c
int		execute_pipeline(t_list *commands);

// pipeline_utils.c
void	init_pipefd(int pipefd[2][2]);
void	set_pipe(int pipefd[2][2], int idx, bool is_last);
void	close_pipe(int pipefd[2][2], int idx, bool is_last);
void	close_pipe_all(int pipefd[2][2]);

// single_cmd.c
int		execute_single_cmd(t_command *command, bool is_subshell);
void	execute_pipeline_single_cmd(t_command *command, bool is_subshell);
char	**get_argv_array(t_list *list);

// builtin.c
int		execute_builtin(t_command *command, int idx, bool is_subshell);
int		get_builtin_function_idx(t_list *argv);

// not_builtin.c
void	execute_not_builtin(t_command *command);

// redirection.c
int		redirect(t_command *command);
int		redirect_builtin(t_command *command, int *old_fd_in, int *old_fd_out);
void	redirect_undo(int old_fd_in, int old_fd_out);

#endif // EXECUTOR_H
