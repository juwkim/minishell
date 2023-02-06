/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_commands_tree.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:43:39 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/06 16:35:51 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

static t_commands_tree	*create_cmd_tree(int type);

t_commands_tree	*make_commands_tree(t_deque *commands, int start, int end)
{
	t_commands_tree	*cmd_tree;
	int				bin_op_idx;

	if (start == end)
	{
		cmd_tree = create_cmd_tree(get_command(commands, start)->types);
		cmd_tree->cmd = get_command(commands, start);
	}
	else if (get_command(commands, start)->types == O_PARENTHESIS)
	{
		
	}
	return (cmd_tree);
}

void	destroy_commands_tree(t_commands_tree *cmd_tree)
{
	if (cmd_tree->sibling != NULL)
		destroy_commands_tree(cmd_tree->sibling);
	if (cmd_tree->child != NULL)
		destroy_commands_tree(cmd_tree->child);
	free(cmd_tree);
}

t_commands_tree	*create_cmd_tree(int type)
{
	t_commands_tree *const	cmd_tree = malloc(sizeof(t_commands_tree));

	cmd_tree->sibling = NULL;
	cmd_tree->child = NULL;
	cmd_tree->type = type;
	return (cmd_tree);
}
