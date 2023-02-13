/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:02:23 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/13 10:40:47 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

int	execute_builtin(t_command *command, int idx, bool is_subshell)
{
	int				old_fd_in;
	int				old_fd_out;
	int				exit_status;
	char			**argv;
	static int		(*func[6])(char **argv) = {builtin_echo, builtin_cd, \
				builtin_pwd, builtin_env, builtin_export, builtin_unset};

	if (redirect_builtin(command, &old_fd_in, &old_fd_out) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (list_is_empty(&command->argv) == true)
	{
		redirect_undo(old_fd_in, old_fd_out);
		return (EXIT_SUCCESS);
	}
	if (expand_wildcard(&command->argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	argv = get_argv_array(&command->argv);
	if (argv == NULL)
		return (EXIT_FAILURE);
	if (idx == 6)
		builtin_exit(argv, is_subshell);
	exit_status = func[idx](argv);
	redirect_undo(old_fd_in, old_fd_out);
	free(argv);
	return (exit_status);
}

int	get_builtin_function_idx(t_list *argv)
{
	const char	*builtin[7] = \
	{"echo", "cd", "pwd", "env", "export", "unset", "exit"};
	int			idx;
	char		*name;

	if (list_is_empty(argv) == true)
		return (NOT_BUILTIN);
	name = list_front(argv);
	idx = 0;
	while (idx < BUILTIN_FUNC_CNT && ft_strcmp(name, builtin[idx]))
		++idx;
	if (idx == BUILTIN_FUNC_CNT)
		return (NOT_BUILTIN);
	return (idx);
}
