/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:35:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 10:53:38 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <sys/stat.h>

# include "global.h"
# include "expander/expander.h"
# include "builtin/builtin.h"
# include "utils/exit_status.h"
# include "utils/environment.h"
# include "utils/signal_handler.h"

# define READ	0
# define WRITE	1

typedef struct s_builtin
{
	const char	*name;
	void		(*func)(char **argv);
}	t_builtin;

// executor.c
int		execute(t_list *commands, bool is_subshell);
int		execute_wait_pid(int last_pid);
int		execute_wait_pid_all(int last_pid);

// group.c
int		execute_group(t_list *commands);

// pipeline.c
int		execute_pipeline(t_list *commands);

// single_cmd.c
int		execute_single_cmd(t_command *command, bool is_subshell);
void	execute_pipeline_single_cmd(t_command *command, bool is_subshell);

// not_builtin.c
void	execute_not_builtin(char **argv);

// redirection.c
int		redirect(t_command *command);

#endif // EXECUTOR_H
