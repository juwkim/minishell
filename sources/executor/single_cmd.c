/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:52:32 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/13 10:39:40 by juwkim           ###   ########.fr       */
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
	char **const	argv = malloc(sizeof(char *) * (list->size + 2));
	t_node			*cur;
	int				idx;

	cur = list->head->next;
	idx = 0;
	while (cur)
	{
		argv[idx++] = cur->item;
		cur = cur->next;
	}
	if (ft_strcmp(argv[0], "ls") == 0 || \
		ft_strcmp(argv[0], "grep") == 0)
		argv[idx++] = "--color=auto";
	argv[idx] = NULL;
	return (argv);
}
