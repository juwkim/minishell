/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:26:55 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/28 01:07:16 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

void	dq_print(t_deque *dq)
{	
	int	cur;

	printf("size [%ld]\n", dq_size(dq));
	cur = dq->head;
	while (cur != dq->tail)
	{
		printf("%s\n", (char *) dq->items[cur]);
		cur = (cur + 1) % QUEUE_SIZE;
	}
}
