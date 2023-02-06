/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_commands_tree.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:43:39 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/06 09:03:26 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

// bool	make_commands_tree(t_linked_list *commands_tree, t_deque *commands)
// {
// 	list_init(&12	)
// }

void	destroy_commands_tree(t_commands_tree *cmd_tree)
{
	t_linked_list	*list;

	list = &cmd_tree->cmd_list;
	while (list->head->next != NULL)
		list_pop_front(list);
	free(list->head);
	list_destroy(&cmd_tree->cmd_list);
}
