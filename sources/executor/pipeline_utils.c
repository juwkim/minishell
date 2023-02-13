/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:14:04 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/13 11:16:28 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

void	init_pipefd(int pipefd[2][2])
{
	pipefd[0][0] = -1;
	pipefd[0][1] = -1;
	pipefd[1][0] = -1;
	pipefd[1][1] = -1;
}

void	set_pipe(int pipefd[2][2], int idx, bool is_last)
{
	const int	prev = (idx + 1) & 1;
	const int	next = idx & 1;

	if (idx == 0)
		dup2(pipefd[next][WRITE], STDOUT_FILENO);
	else if (is_last)
		dup2(pipefd[prev][READ], STDIN_FILENO);
	else
	{
		dup2(pipefd[prev][READ], STDIN_FILENO);
		dup2(pipefd[next][WRITE], STDOUT_FILENO);
	}
	close_pipe_all(pipefd);
}

void	close_pipe(int pipefd[2][2], int idx, bool is_last)
{
	const int	prev = (idx + 1) & 1;
	const int	next = idx & 1;

	if (idx == 0)
		close(pipefd[next][WRITE]);
	else if (is_last == true)
		close(pipefd[prev][READ]);
	else
	{
		close(pipefd[prev][READ]);
		close(pipefd[next][WRITE]);
	}
}

void	close_pipe_all(int pipefd[2][2])
{
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	close(pipefd[1][0]);
	close(pipefd[1][1]);
}
