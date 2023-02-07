/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:35:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/08 06:16:25 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>

# include "global.h"
# include "parser/parser.h"

# define READ	0
# define WRITE	1

// executor.c
int		execute(t_list *commands, bool is_subshell);
int		execute_wait_pid(int last_pid);
int		execute_wait_pid_all(int last_pid);

// executor/excutor_group.c
int		execute_group(t_list *commands);

// executor/excutor_pipeline.c
int		execute_pipeline(t_list *commands);

// executor/executor_cmd.c
int		execute_cmd(t_command *command, bool is_subshell);

// executor_exit_status.c
int		exit_status_get(void);
void	exit_status_set(int status);

#endif // EXECUTOR_H
