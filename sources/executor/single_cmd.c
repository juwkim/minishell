/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:52:32 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 16:56:12 by juwkim           ###   ########.fr       */
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
	if (expand_wildcard(&command->argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	argv = get_argv_array(&command->argv);
	if (argv == NULL)
		return (EXIT_FAILURE);
	if (ft_strcmp(argv[0], "exit") == 0)
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
	if (expand_wildcard(&command->argv) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
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

static void	execute_function(char **argv)
{
	const t_builtin	builtin[6] = \
	{{"echo", builtin_echo}, {"cd", builtin_cd}, {"pwd", builtin_pwd}, \
	{"env", builtin_env}, {"export", builtin_export}, {"unset", builtin_unset}};
	int				idx;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	idx = 0;
	while (idx < BUILTIN_FUNC_CNT - 1 && ft_strcmp(argv[0], builtin[idx].name))
		++idx;
	if (idx == BUILTIN_FUNC_CNT - 1)
		execute_not_builtin(argv);
	else
		builtin[idx].func(argv);
}
