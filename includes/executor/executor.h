/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:35:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 08:58:43 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <sys/stat.h>

# include "global.h"
# include "builtin/builtin.h"
# include "utils/environment.h"
# include "utils/signal_handler.h"

// POSIX BASED EXIT STATUS
# define EXIT_MISUSE_SHELL_BUILTIN	2 // misuse of shell builtins
# define EXIT_NOEXEC				126 // command invoked cannot execute
# define EXIT_NOTFOUND				127 // command not found

# define READ	0
# define WRITE	1

# define EVERYTING_IS_GOOD 2 // preprocessing is good

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

// group.c
int		execute_group(t_list *commands);

// pipeline.c
int		execute_pipeline(t_list *commands);

// cmd.c
int		execute_cmd(t_command *command, bool is_subshell, bool is_pipeline);

// exit_status.c
int		exit_status_get(void);
void	exit_status_set(int status);

// not_builtin.c
int		execute_not_builtin(char **argv, bool is_pipeline);

// redirection.c
bool	redirect(t_command *command, int *oldfd_in, int *oldfd_out);
bool	redirect_undo(int oldfd_in, int oldfd_out);

#endif // EXECUTOR_H
