/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tree_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 06:47:04 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/07 01:44:32 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_tree/command_tree.h"

int	get_group_end_idx(t_deque *commands, int start)
{
	t_command	*cmd;
	int			opened;
	int			end;

	opened = 1;
	end = start;
	while (opened != 0)
	{
		cmd = get_command(commands, ++end);
		if (cmd->types == O_PARENTHESIS)
			++opened;
		else if (cmd->types == C_PARENTHESIS)
			--opened;
	}
	return (end);
}

// int	get_pipe_end_idx(t_deque *commands, int start)
// {
// 	++idx;
// 	while (idx != commands->tail && get_command(commands, idx)->types == PIPE)
// 	{
// 		if (get_command(commands, idx + 1)->types == O_PARENTHESIS)
// 			idx = get_parenthesis_skipped_idx(commands, idx);
// 		else if (idx + 2 == commands->tail ||
// 			get_command(commands, idx + 2)->types == PIPE)
// 			idx += 2;
// 	}
// 	return (idx);
// }
