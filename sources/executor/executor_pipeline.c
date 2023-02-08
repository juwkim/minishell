/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:50:49 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/08 14:11:39 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static void	execute_pipeline_cmd(t_command *cmd, int pipefd[2][2], \
												int idx, bool is_last);
static void	execute_pipe_set(int pipefd[2][2], int idx, bool is_last);

int	execute_pipeline(t_list *commands)
{
	t_node	*cur;
	int		pid;
	int		idx;
	int		pipefd[2][2];

	idx = 0;
	pid = 0;
	cur = commands->head->next;
	while (cur && pid != -1)
	{
		if (cur->next != NULL && pipe(pipefd[idx & 1]) == -1)
			break ;
		pid = fork();
		if (pid == 0)
			execute_pipeline_cmd(cur->item, pipefd, idx, cur->next == NULL);
		else if (cur->next != NULL)
		{
			close(pipefd[idx & 1][READ]);
			close(pipefd[idx++ & 1][WRITE]);
		}
		if (cur->next == NULL)
			break ;
		cur = cur->next->next;
	}
	return (execute_wait_pid_all(pid));
}

static void	execute_pipeline_cmd(t_command *cmd, int pipefd[2][2], \
												int idx, bool is_last)
{
	int	exit_status;

	exit_status = 0;
	execute_pipe_set(pipefd, idx, is_last);
	if (cmd->type == CMD)
		exit_status = execute_cmd(cmd, true);
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
	{
		dup2(pipefd[next][WRITE], STDOUT_FILENO);
		close(pipefd[next][READ]);
		close(pipefd[next][WRITE]);
		return ;
	}
	else if (is_last)
		dup2(pipefd[prev][READ], STDIN_FILENO);
	else
	{
		dup2(pipefd[prev][READ], STDIN_FILENO);
		dup2(pipefd[next][WRITE], STDOUT_FILENO);
	}
	close(pipefd[prev][READ]);
	close(pipefd[prev][WRITE]);
	close(pipefd[next][READ]);
	close(pipefd[next][WRITE]);
}
