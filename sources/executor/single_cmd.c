/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:52:32 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/14 05:51:08 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

int	execute_single_cmd(t_command *command, bool is_subshell)
{
	int			pid;
	const int	idx = get_builtin_function_idx(&command->argv);

	if (idx != NOT_BUILTIN)
		return (execute_builtin(command, idx, is_subshell));
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
		execute_not_builtin(command);
	return (execute_wait_pid(pid));
}

void	execute_pipeline_single_cmd(t_command *command, bool is_subshell)
{
	const int	idx = get_builtin_function_idx(&command->argv);

	if (idx != NOT_BUILTIN)
		exit(execute_builtin(command, idx, is_subshell));
	execute_not_builtin(command);
}

char	**get_argv_array(t_list *list)
{
	char **const	argv = malloc(sizeof(char *) * (list->size + 1));
	t_node			*cur;
	int				idx;

	cur = list->head->next;
	idx = 0;
	while (cur)
	{
		argv[idx++] = cur->item;
		cur = cur->next;
	}
	argv[idx] = NULL;
	return (argv);
}
