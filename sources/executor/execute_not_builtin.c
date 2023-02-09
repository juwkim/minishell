/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_not_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:20:13 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/09 09:07:50 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static void	execute_not_builtin_func(char **argv);
static char	*get_cmd_path(char *file);
static char	**get_splited_path(void);

int	execute_not_builtin(char **argv)
{
	const int	pid = fork();

	if (pid == -1)
	{
		print_error(NULL, NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		execute_not_builtin_func(argv);
	return (execute_wait_pid(pid));
}

static void	execute_not_builtin_func(char **argv)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ft_strchr(argv[0], '/') == NULL)
	{
		argv[0] = get_cmd_path(argv[0]);
		if (argv[0] == NULL)
		{
			print_error(argv[0], NULL, "command not found");
			exit(EXEC_NOTFOUND);
		}
	}
	execve(argv[0], argv, g_env.item);
	if (errno == ENOENT)
		exit(EXEC_NOTFOUND);
	else
		exit(EXEC_NOEXEC);
}

static char	*get_cmd_path(char *file)
{
	char		**splited_path;
	char		*bin_path;
	int			idx;
	struct stat	s;

	splited_path = get_splited_path();
	if (splited_path == NULL)
		return (NULL);
	idx = 0;
	while (splited_path[idx])
	{
		if (splited_path[idx][ft_strlen(splited_path[idx]) - 1] == '/')
			bin_path = ft_strjoin(splited_path[idx], file);
		else
			bin_path = ft_strcjoin(splited_path[idx], file, '/');
		if (access(bin_path, F_OK) == 0 && stat(bin_path, &s) == 0 && \
											S_ISDIR(s.st_mode) == false)
			break ;
		free(bin_path);
		bin_path = NULL;
		++idx;
	}
	ft_free_array(splited_path);
	return (bin_path);
}

static char	**get_splited_path(void)
{
	const char	*path = env_get("PATH");

	if (path == NULL)
		return (NULL);
	return (ft_split(path, ':'));
}
