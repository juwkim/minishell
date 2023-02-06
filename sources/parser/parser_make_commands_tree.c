/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_commands_tree.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:43:39 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/06 14:01:59 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

t_commands_tree	*make_commands_tree(t_deque *commands, int start, int end)
{
	int	bin_op_idx;

	bin_op_idx = start + 1;
	while (bin_op_idx != end && \
				(get_command(commands, bin_op_idx)->types & (AND | OR)) == 0)
		++bin_op_idx;
}

void	destroy_commands_tree(t_commands_tree *cmd_tree)
{
	if (cmd_tree->sibling != NULL)
		destroy_commands_tree(cmd_tree->sibling);
	if (cmd_tree->child != NULL)
		destroy_commands_tree(cmd_tree->child);
	free(cmd_tree);
}
