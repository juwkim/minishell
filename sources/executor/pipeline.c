/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:50:49 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/13 11:20:02 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static void	execute_pipeline_cmd(t_command *cmd, int pipefd[2][2], \
												int idx, bool is_last);

int	execute_pipeline(t_list *commands)
{
	t_node	*cur;
	int		pid;
	int		idx;
	int		pipefd[2][2];

	idx = 0;
	pid = 0;
	cur = commands->head->next;
	init_pipefd(pipefd);
	while (cur)
	{
		if (cur->next != NULL && pipe(pipefd[idx & 1]) == -1)
			break ;
		pid = fork();
		if (pid == -1)
			break ;
		if (pid == 0)
			execute_pipeline_cmd(cur->item, pipefd, idx, cur->next == NULL);
		close_pipe(pipefd, idx, cur->next == NULL);
		if (cur->next == NULL)
			break ;
		++idx;
		cur = cur->next->next;
	}
	return (execute_wait_pid_all(pid));
}

static void	execute_pipeline_cmd(t_command *cmd, int pipefd[2][2], \
												int idx, bool is_last)
{
	set_pipe(pipefd, idx, is_last);
	if (cmd->type == CMD)
		execute_pipeline_single_cmd(cmd, true);
	else if (cmd->type == GROUP)
		exit(execute_group(&cmd->argv));
	else if (cmd->type == PIPELINE)
		exit(execute_pipeline(&cmd->argv));
}
