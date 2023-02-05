/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 03:11:46 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/04 07:44:24 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static int	execute_group(t_deque *commands, int start, int end);

int	execute(t_deque *commands, int start, int end, bool is_subshell)
{
	if (start + 1 != end && get_command(commands, start + 1)->types == PIPE)
		exit_status_set(execute_pipeline(commands, start, end));
	else if (get_command(commands, start)->types == O_PARENTHESIS)
		exit_status_set(execute_group(commands, start, end));
	else
		exit_status_set(executr_cmd(commands, start, is_subshell));
	start = get_operator_skipped_idx(commands, &start);
	if (start != end)
		exit_status_set(execute(commands, start, end, is_subshell));
	return (exit_status_get());
}

static int	execute_group(t_deque *commands, int start, int end)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		print_error(NULL, NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		status = execute(cmd_content(l_cmd)->l_element, true, l_free);
		exec_free_all(NULL, l_free);
		exit(status);
	}
	return (exec_wait_pid(pid, NULL));
}
