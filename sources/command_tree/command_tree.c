/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:43:39 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/07 01:53:43 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_tree/command_tree.h"

t_tree_node	*merge_group_commands(t_deque *commands, int start, int end);
t_tree_node	*tree_insert(t_tree_node *cmd_tree, t_tree_node *node);
t_tree_node	*tree_create_node(int type);

t_tree_node	*make_commands_tree(t_deque *commands, int start, int end)
{
	t_tree_node	*cmd_tree;

	cmd_tree = merge_group_commands(commands, start, end);

	return (cmd_tree);
}

t_tree_node	*merge_group_commands(t_deque *commands, int start, int end)
{
	t_tree_node	*cmd_tree;
	t_tree_node	*node;
	t_command	*cmd;
	int			group_end_idx;

	cmd_tree = NULL;
	while (start <= end)
	{
		cmd = get_command(commands, start);
		if (cmd->types == O_PARENTHESIS)
		{
			group_end_idx = get_group_end_idx(commands, start);
			node = merge_group_commands(commands, start + 1, group_end_idx - 1);
			node->type = GROUP;
			start = group_end_idx + 1;
		}
		else
		{
			node = tree_create_node(cmd->types);
			++start;
		}
		tree_insert(cmd_tree, node);
	}
	return (cmd_tree);
}

t_tree_node	*tree_insert(t_tree_node *cmd_tree, t_tree_node *node)
{
	t_tree_node	*cur;

	if (cmd_tree == NULL)
		return (node);
	cur = cmd_tree;
	while (cur->child != NULL)
		cur = cur->child;
	cur->child = node;
	return (cmd_tree);
}

void	tree_destroy(t_tree_node *cmd_tree)
{
	if (cmd_tree == NULL)
		return ;
	tree_destroy(cmd_tree->child);
	free(cmd_tree);
}

t_tree_node	*tree_create_node(int type)
{
	t_tree_node *const	tree_node = malloc(sizeof(t_tree_node));

	if (tree_node == NULL)
		return (NULL);
	tree_node->child = NULL;
	tree_node->type = type;
	return (tree_node);
}
