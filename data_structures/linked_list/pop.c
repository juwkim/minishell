/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 06:40:11 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/31 03:56:02 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	list_pop_front(t_linked_list *list)
{
	list_erase(list, 0);
}

void	list_pop_back(t_linked_list *list)
{
	list_erase(list, list->size - 1);
}

void	list_erase(t_linked_list *list, int pos)
{
	t_node	*cur;
	t_node	*temp;

	cur = list->head;
	while (pos--)
		cur = cur->next;
	temp = cur->next;
	cur->next = cur->next->next;
	--list->size;
	free(temp->item);
	free(temp);
}
