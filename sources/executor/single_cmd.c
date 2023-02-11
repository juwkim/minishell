/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:52:32 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 07:08:38 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static char	**get_argv_array(t_list *list);
static void	execute_function(char **argv);

int	execute_single_cmd(t_command *command, bool is_subshell)
{
	int		pid;
	char	**argv;

	if (ft_strncmp(list_front(&command->argv), "exit", ft_strlen("exit")) != 0)
	{
		pid = fork();
		if (pid == -1)
			return (EXIT_FAILURE);
		if (pid != 0)
			return (execute_wait_pid(pid));
	}
	if (redirect(command) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (list_is_empty(&command->argv) == true)
		return (EXIT_SUCCESS);
	argv = get_argv_array(&command->argv);
	if (argv == NULL)
		return (EXIT_FAILURE);
	if (ft_strncmp(argv[0], "exit", ft_strlen("exit")) == 0)
		builtin_exit(argv, is_subshell);
	execute_function(argv);
	return (EXIT_SUCCESS);
}

void	execute_pipeline_single_cmd(t_command *command, bool is_subshell)
{
	char	**argv;

	if (redirect(command) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (list_is_empty(&command->argv) == true)
		exit(EXIT_SUCCESS);
	argv = get_argv_array(&command->argv);
	if (argv == NULL)
		exit(EXIT_FAILURE);
	if (ft_strncmp(argv[0], "exit", ft_strlen("exit")) == 0)
		builtin_exit(argv, is_subshell);
	execute_function(argv);
}

static char	**get_argv_array(t_list *list)
{
	char **const	argv = malloc(sizeof(char *) * (list->size + 2));
	t_node			*cur;
	int				idx;

	if (argv == NULL)
	{
		print_error("Executor", "get_argv_array", NULL);
		return (NULL);
	}
	cur = list->head->next;
	idx = 0;
	while (cur)
	{
		argv[idx++] = cur->item;
		cur = cur->next;
	}
	if (ft_strncmp(argv[0], "ls", 2) == 0 || \
		ft_strncmp(argv[0], "grep", 2) == 0)
		argv[idx++] = "--color=auto";
	argv[idx] = NULL;
	return (argv);
}

static void	execute_function(char **argv)
{
	const t_builtin	builtin[6] = \
	{{"echo", 4, builtin_echo}, {"cd", 2, builtin_cd}, \
	{"pwd", 3, builtin_pwd}, {"env", 3, builtin_env}, \
	{"export", 6, builtin_export}, {"unset", 5, builtin_unset}};
	int				idx;

	idx = 0;
	while (idx < BUILTIN_FUNC_CNT - 1 && \
		ft_strncmp(argv[0], builtin[idx].name, builtin[idx].name_len) != 0)
		++idx;
	if (idx == BUILTIN_FUNC_CNT - 1)
		execute_not_builtin(argv);
	else
		builtin[idx].func(argv);
}
