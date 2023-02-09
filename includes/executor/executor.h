/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:35:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/10 04:11:49 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <sys/stat.h>

# include "global.h"
# include "parser/parser.h"
# include "builtin/builtin.h"

// POSIX BASED EXIT STATUS
# define EXEC_NOEXEC	126 // command invoked cannot execute
# define EXEC_NOTFOUND	127 // command not found

# define READ	0
# define WRITE	1

typedef struct s_builtin
{
	const char	*name;
	int			name_len;
	int			(*func)(char **argv);
}	t_builtin;

// executor.c
int		execute(t_list *commands, bool is_subshell);
int		execute_wait_pid(int last_pid);
int		execute_wait_pid_all(int last_pid);

// executor/excutor_group.c
int		execute_group(t_list *commands);

// executor/excutor_pipeline.c
int		execute_pipeline(t_list *commands);

// executor/executor_cmd.c
int		execute_cmd(t_command *command, bool is_subshell, bool is_pipeline);

// executor_exit_status.c
int		exit_status_get(void);
void	exit_status_set(int status);

// executor_not_builtin.c
int		execute_not_builtin(char **argv, bool is_pipeline);

#endif // EXECUTOR_H
