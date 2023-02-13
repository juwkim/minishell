/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:50:49 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/13 10:57:14 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static void	execute_pipeline_cmd(t_command *cmd, int pipefd[2][2], \
												int idx, bool is_last);
static void	execute_pipe_set(int pipefd[2][2], int idx, bool is_last);
static void	close_pipefd(int pipefd[2][2], int idx, bool is_last);
static void	close_pipefd_all(int pipefd[2][2]);

int	execute_pipeline(t_list *commands)
{
	t_node		*cur;
	int			pid;
	int			idx;
	static int	pipefd[2][2] = {{-1, -1}, {-1, -1}};

	idx = 0;
	pid = 0;
	cur = commands->head->next;
	while (cur)
	{
		if (cur->next != NULL && pipe(pipefd[idx & 1]) == -1)
			break ;
		pid = fork();
		if (pid == -1)
			break ;
		if (pid == 0)
			execute_pipeline_cmd(cur->item, pipefd, idx, cur->next == NULL);
		if (cur->next == NULL)
			break ;
		close_pipefd(pipefd, idx, cur->next == NULL);
		++idx;
		cur = cur->next->next;
	}
	return (execute_wait_pid_all(pid));
}

static void	execute_pipeline_cmd(t_command *cmd, int pipefd[2][2], \
												int idx, bool is_last)
{
	execute_pipe_set(pipefd, idx, is_last);
	if (cmd->type == CMD)
		execute_pipeline_single_cmd(cmd, true);
	else if (cmd->type == GROUP)
		exit(execute_group(&cmd->argv));
	else if (cmd->type == PIPELINE)
		exit(execute_pipeline(&cmd->argv));
}

static void	execute_pipe_set(int pipefd[2][2], int idx, bool is_last)
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
	close_pipefd_all(pipefd);
}

static void	close_pipefd(int pipefd[2][2], int idx, bool is_last)
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

static void	close_pipefd_all(int pipefd[2][2])
{
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	close(pipefd[1][0]);
	close(pipefd[1][1]);
}
