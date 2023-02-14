/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 03:11:46 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/14 11:13:46 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static bool	is_operator_skip(int command_type);

int	execute(t_list *commands, bool is_subshell)
{
	t_node		*cur;
	t_command	*cmd;

	cur = commands->head->next;
	while (cur != NULL)
	{
		cmd = cur->item;
		if (cmd->type == CMD)
			exit_status_set(execute_single_cmd(cmd, is_subshell));
		else if (cmd->type == GROUP)
			exit_status_set(execute_group(&cmd->argv));
		else
			exit_status_set(execute_pipeline(&cmd->argv));
		cur = cur->next;
		while (cur && is_operator_skip(((t_command *)cur->item)->type))
			cur = cur->next->next;
		if (cur != NULL)
			cur = cur->next;
	}
	list_destroy(commands, destroy_command);
	return (exit_status_get());
}

static bool	is_operator_skip(int command_type)
{
	return (((command_type == AND) && exit_status_get() != 0) || \
			((command_type == OR) && exit_status_get() == 0));
}

int	execute_wait_pid(int last_pid)
{
	int	status;
	int	exit_status;

	signal(SIGINT, SIG_IGN);
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		if (status != SIGPIPE)
			write(STDERR_FILENO, "\n", ft_strlen("\n"));
		exit_status = 128 + WTERMSIG(status);
	}
	else
		exit_status = EXIT_FAILURE;
	signal(SIGINT, sigint_handler);
	return (exit_status);
}

int	execute_wait_pid_all(int last_pid)
{
	const int	exit_status = execute_wait_pid(last_pid);

	while (wait(NULL) != -1)
		;
	errno = 0;
	return (exit_status);
}
