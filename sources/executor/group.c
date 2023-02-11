/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:49:26 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 05:39:04 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

int	execute_group(t_list *commands)
{
	const int	pid = fork();

	if (pid == -1)
		return (print_error(NULL, NULL, NULL));
	if (pid == 0)
		exit(execute(commands, true));
	return (execute_wait_pid(pid));
}
