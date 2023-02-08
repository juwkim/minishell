/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:52:32 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/09 03:31:11 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static int	execute_function(t_list *argv, bool is_subshell);

int	execute_cmd(t_command *command, bool is_subshell)
{
	int	exit_status;

	// redirection
	if (list_is_empty(&command->argv))
		return (EXIT_SUCCESS);
	exit_status = execute_function(&command->argv, is_subshell);
	// redirection undo
	return (exit_status);
}

static int	execute_function(t_list *argv, bool is_subshell)
{
	const t_builtin	builtin[6] = \
	{
	{"echo", 4, builtin_echo}, {"cd", 2, builtin_cd}, \
	{"pwd", 3, builtin_pwd}, {"env", 3, builtin_env}, \
	{"export", 6, builtin_export}, {"unset", 5, builtin_unset}
	};
	int				idx;
	const char		*name = list_front(argv);

	if (ft_strncmp(name, "exit", ft_strlen("exit")) == 0)
		return (builtin_exit(argv, is_subshell));
	idx = 0;
	while (idx < BUILTIN_FUNC_CNT - 1 && \
		ft_strncmp(name, builtin[idx].name, builtin[idx].name_len) != 0)
		++idx;
	if (idx == BUILTIN_FUNC_CNT - 1)
		return (execute_not_builtin(argv));
	else
		return (builtin[idx].func(argv));
}
