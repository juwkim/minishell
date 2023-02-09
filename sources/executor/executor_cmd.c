/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:52:32 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/10 07:03:02 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static char	**get_argv_array(t_list *list);
static int	execute_function(char **argv, bool is_subshell, bool is_pipeline);

int	execute_cmd(t_command *command, bool is_subshell, bool is_pipeline)
{
	int			exit_status;
	char		**argv;
	const int	oldfd_in = dup(STDIN_FILENO);
	const int	oldfd_out = dup(STDOUT_FILENO);

	if (oldfd_in == -1 || oldfd_out == -1)
	{
		print_error(NULL, NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (redirect(command) == false || list_is_empty(&command->argv))
		return (EXIT_FAILURE);
	argv = get_argv_array(&command->argv);
	if (argv == NULL)
	{
		print_error(NULL, NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
	exit_status = execute_function(argv, is_subshell, is_pipeline);
	free(argv);
	if (redirect_undo(oldfd_in, oldfd_out) == false)
		return (EXIT_FAILURE);
	return (exit_status);
}

static char	**get_argv_array(t_list *list)
{
	char **const	argv = malloc(sizeof(char *) * (list->size + 1));
	t_node			*cur;
	int				idx;

	if (argv == NULL)
		return (NULL);
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

static int	execute_function(char **argv, bool is_subshell, bool is_pipeline)
{
	const t_builtin	builtin[6] = \
	{{"echo", 4, builtin_echo}, {"cd", 2, builtin_cd}, \
	{"pwd", 3, builtin_pwd}, {"env", 3, builtin_env}, \
	{"export", 6, builtin_export}, {"unset", 5, builtin_unset}};
	int				idx;
	const char		*name = argv[0];

	if (ft_strncmp(name, "exit", ft_strlen("exit")) == 0)
		return (builtin_exit(argv, is_subshell));
	idx = 0;
	while (idx < BUILTIN_FUNC_CNT - 1 && \
		ft_strncmp(name, builtin[idx].name, builtin[idx].name_len) != 0)
		++idx;
	if (idx == BUILTIN_FUNC_CNT - 1)
		return (execute_not_builtin(argv, is_pipeline));
	else
		return (builtin[idx].func(argv));
}
