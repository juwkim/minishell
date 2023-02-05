/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_operator_skip.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 06:47:04 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/04 07:27:43 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static bool	is_operator_skip(int command_type);
static int	get_parenthesis_skipped_idx(t_deque *commands, int idx);
static int	get_pipe_skipped_idx(t_deque *commands, int idx);

int	get_operator_skipped_idx(t_deque *commands, int idx)
{
	t_command	*cmd;

	cmd = commands->items[idx];
	while (idx != commands->tail && is_operator_skip(cmd->types) == true)
	{
		++idx;
		if (get_command(commands, idx)->types == O_PARENTHESIS)
			idx = get_parenthesis_skipped_idx(commands, idx);
		else if (get_command(commands, idx + 1)->types == PIPE)
			idx = get_pipe_skipped_idx(commands, idx);
		else
			++idx;
	}
	return (idx);
}

static bool	is_operator_skip(int command_type)
{
	return (((command_type & AND) && exit_status_get() != 0) || \
			((command_type & OR) && exit_status_get() == 0));
}

static int	get_parenthesis_skipped_idx(t_deque *commands, int idx)
{
	t_command	*cmd;
	int			opened;

	++idx;
	opened = 1;
	cmd = get_command(commands, idx);
	while (opened != 0)
	{
		if (cmd->types == O_PARENTHESIS)
			++opened;
		else if (cmd->types == C_PARENTHESIS)
			--opened;
		++idx;
		cmd = get_command(commands, idx);
	}
	return (idx);
}

static int	get_pipe_skipped_idx(t_deque *commands, int idx)
{
	++idx;
	while (idx != commands->tail && get_command(commands, idx)->types == PIPE)
	{
		if (get_command(commands, idx + 1)->types == O_PARENTHESIS)
			idx = get_parenthesis_skipped_idx(commands, idx);
		else if (idx + 2 != commands->tail && \
			get_command(commands, idx + 2)->types == PIPE)
			idx += 2;
	}
	++idx;
	return (idx);
}
