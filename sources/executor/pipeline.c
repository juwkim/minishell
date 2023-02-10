/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:50:49 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 06:54:04 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static void	execute_pipeline_cmd(t_command *cmd, int pipefd[2][2], \
												int idx, bool is_last);
static void	execute_pipe_set(int pipefd[2][2], int idx, bool is_last);
static bool	close_pipefd(int idx);

int	execute_pipeline(t_list *commands)
{
	t_node	*cur;
	int		pid;
	int		idx;
	int		pipefd[2][2];

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
		++idx;
		cur = cur->next->next;
	}
	if (close_pipefd(idx) == false)
		print_error(NULL, NULL);
	return (execute_wait_pid_all(pid));
}

static void	execute_pipeline_cmd(t_command *cmd, int pipefd[2][2], \
												int idx, bool is_last)
{
	int	exit_status;

	exit_status = 0;
	execute_pipe_set(pipefd, idx, is_last);
	if (cmd->type == CMD)
		exit_status = execute_cmd(cmd, true, true);
	else if (cmd->type == GROUP)
		exit_status = execute_group(&cmd->argv);
	else if (cmd->type == PIPELINE)
		exit_status = execute_pipeline(&cmd->argv);
	exit(exit_status);
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
	if (close_pipefd(idx) == false)
		print_error(NULL, NULL);
}

static bool	close_pipefd(int idx)
{
	int		cnt;
	bool	res;

	cnt = 0;
	res = true;
	while (cnt < idx)
	{
		if (close(2 * cnt + 3) == -1)
			res = false;
		if (close(2 * cnt + 4) == -1)
			res = false;
		++cnt;
	}
	return (res);
}
