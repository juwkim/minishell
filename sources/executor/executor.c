/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 03:11:46 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/06 08:01:37 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static int	execute_group(t_deque *commands, int start, int end);
static int	execute_pipeline(t_deque *commands, int start, int end);
static int	execute_cmd(t_command *command, bool is_subshell);
// static int	execute_wait_pid(int last_pid, char *name);

int	execute(t_deque *commands, int start, int end, bool is_subshell)
{
	int	next;

	if (start + 1 != end && get_command(commands, start + 1)->types == PIPE)
	{
		next = get_pipe_skipped_idx(commands, start);
		exit_status_set(execute_pipeline(commands, start, next));
	}
	else if (get_command(commands, start)->types == O_PARENTHESIS)
	{
		next = get_parenthesis_skipped_idx(commands, start);
		exit_status_set(execute_group(commands, start, next));
	}
	else
	{
		next = start + 1;
		exit_status_set(execute_cmd(commands->items[start], is_subshell));
	}
	next = get_operator_skipped_idx(commands, next);
	if (next != end)
		exit_status_set(execute(commands, next, end, is_subshell));
	return (exit_status_get());
}

static int	execute_cmd(t_command *command, bool is_subshell)
{
	printf("i am in %s and %d\n", list_front(&command->argv), is_subshell);
	return (0);
}

static int	execute_group(t_deque *commands, int start, int end)
{
	// int	pid;
	// int	status;

	// pid = fork();
	// if (pid == -1)
	// {
	// 	print_error(NULL, NULL, strerror(errno));
	// 	return (EXIT_FAILURE);
	// }
	// if (pid == 0)
	// {
	// 	status = execute(commands, start, end, true);
	// 	destroy_commands(commands);
	// 	exit(status);
	// }
	// return (execute_wait_pid(pid, NULL));
	(void) commands;
	(void) start;
	(void) end;
	printf("i am in pipe group\n");
	return (0);
}

static int	execute_pipeline(t_deque *commands, int start, int end)
{
	(void) commands;
	(void) start;
	(void) end;

	printf("i am in pipe line\n");
	while (start != end)
	{
		printf("cmd: %s\n", list_front(&get_command(commands, start)->argv));
		++start;
	}
	return (0);
}


// static int	execute_wait_pid(int last_pid, char *name)
// {
// 	int	status;

// 	status = 0;
// 	waitpid(last_pid, &status, 0);
// 	if (WIFSIGNALED(status))
// 	{
// 		if (WTERMSIG(status) == 3)
// 			write(STDERR_FILENO, "Quit: 3\n", ft_strlen("Quit: 3\n"));
// 		else if (WTERMSIG(status) == 2)
// 			write(STDERR_FILENO, "\n", ft_strlen("\n"));
// 		status = 128 + WTERMSIG(status);
// 	}
// 	else if (WIFEXITED(status))
// 		status = WEXITSTATUS(status);
// 	return (status);
// }
