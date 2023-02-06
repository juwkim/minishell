/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tree.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:22:35 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/07 01:51:40 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_TREE_H
# define COMMAND_TREE_H

# include "global.h"
# include "parser/parser.h"

typedef struct s_tree_tree
{
	int					type;
	t_command			*cmd;
	struct s_tree_tree	*child;
}	t_tree_node;

// command_tree.c
t_tree_node	*make_commands_tree(t_deque *commands, int start, int end);
void		tree_destroy(t_tree_node *cmd_tree);

// command_tree_utils.c
int			get_group_end_idx(t_deque *commands, int start);

#endif // COMMAND_TREE_H
