/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:49:26 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 06:54:04 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

int	execute_group(t_list *commands)
{
	int	pid;
	int	exit_status;

	pid = fork();
	if (pid == -1)
	{
		print_error(NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		exit_status = execute(commands, true);
		exit(exit_status);
	}
	return (execute_wait_pid(pid));
}
