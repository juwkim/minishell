/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_not_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:20:13 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/09 01:26:41 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

int	execute_not_builtin(t_list *argv)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (((char *)list_front(argv))[0] == '/' && \
				hash_table_search(&g_env, "PATH") != NULL)
	{
		if (exec_scmd_search_path(argv) == ERROR)
		{
			print_error(SHELL_NAME, argv[0], NULL, "command not found");
			return (EXEC_NOTFOUND);
		}
	}
	execve(argv[0], argv, g_env);
	if (errno == ENOENT)
		status = EXEC_NOTFOUND;
	else
		status = EXEC_NOEXEC;
	print_error_errno(SHELL_NAME, argv[0], NULL);

	return (0);
}
