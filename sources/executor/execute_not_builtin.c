/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_not_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:20:13 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/10 06:53:53 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static void	execute_not_builtin_func(char **argv);
static bool	set_cmd_path(char **argv);
static char	**get_splited_path(void);

int	execute_not_builtin(char **argv, bool is_pipeline)
{
	const int	pid = fork();

	if (pid == -1)
	{
		print_error(NULL, NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		execute_not_builtin_func(argv);
	if (is_pipeline)
		return (EXIT_SUCCESS);
	else
		return (execute_wait_pid(pid));
}

static void	execute_not_builtin_func(char **argv)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ft_strchr(argv[0], '/') == NULL)
	{
		if (set_cmd_path(argv) == false)
		{
			print_error(NULL, NULL, strerror(errno));
			exit(EXIT_FAILURE);
		}
		if (argv[0] == NULL)
		{
			print_error(argv[0], NULL, "command not found");
			exit(EXEC_NOTFOUND);
		}
	}
	execve(argv[0], argv, g_env.item);
}

static bool	set_cmd_path(char **argv)
{
	char		**splited_path;
	char		*bin_path;
	int			idx;
	struct stat	s;

	splited_path = get_splited_path();
	if (splited_path == NULL)
		return (false);
	idx = -1;
	while (splited_path[++idx])
	{
		if (splited_path[idx][ft_strlen(splited_path[idx]) - 1] == '/')
			bin_path = ft_strjoin(splited_path[idx], argv[0]);
		else
			bin_path = ft_strcjoin(splited_path[idx], argv[0], '/');
		if (bin_path == NULL)
			return (false);
		if (access(bin_path, X_OK) == 0 && \
			stat(bin_path, &s) == 0 && S_ISDIR(s.st_mode) == false)
			break ;
		free(bin_path);
		bin_path = NULL;
	}
	argv[0] = bin_path;
	return (true);
}

static char	**get_splited_path(void)
{
	const char	*path = env_get("PATH");

	if (path == NULL)
		return (NULL);
	return (ft_split(path, ':'));
}
