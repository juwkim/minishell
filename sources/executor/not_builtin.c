/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:20:13 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/14 07:31:26 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static int	set_cmd_path(char **argv);
static char	**get_splited_path(void);

void	execute_not_builtin(t_command *command)
{
	char	**argv;
	char	*cmd_name;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (list_is_empty(&command->argv) == true)
		exit(EXIT_SUCCESS);
	if (redirect(command) == EXIT_FAILURE || \
		expand_wildcard(&command->argv) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	argv = get_argv_array(&command->argv);
	if (argv == NULL)
		exit(EXIT_FAILURE);
	cmd_name = argv[0];
	if (ft_strchr(argv[0], '/') == NULL && set_cmd_path(argv) == EXIT_FAILURE)
	{
		print_error(cmd_name, NULL, "command not found");
		exit(EXIT_NOTFOUND);
	}
	execve(argv[0], argv, g_env.item);
	print_error(cmd_name, NULL, NULL);
	if (errno == ENOENT)
		exit(EXIT_NOTFOUND);
	exit(EXIT_NOEXEC);
}

static int	set_cmd_path(char **argv)
{
	char		**splited_path;
	char		*bin_path;
	int			idx;
	struct stat	s;

	splited_path = get_splited_path();
	if (splited_path == NULL)
		return (EXIT_FAILURE);
	idx = -1;
	while (splited_path[++idx])
	{
		if (splited_path[idx][ft_strlen(splited_path[idx]) - 1] == '/')
			bin_path = ft_strjoin(splited_path[idx], argv[0]);
		else
			bin_path = ft_strcjoin(splited_path[idx], argv[0], '/');
		if (bin_path == NULL)
			return (EXIT_FAILURE);
		if (access(bin_path, X_OK) == 0 && \
			stat(bin_path, &s) == 0 && S_ISDIR(s.st_mode) == false)
			break ;
		free(bin_path);
		bin_path = NULL;
	}
	argv[0] = bin_path;
	return (argv[0] == NULL);
}

static char	**get_splited_path(void)
{
	const char	*path = env_get("PATH");

	if (path == NULL)
		return (NULL);
	return (ft_split(path, ':'));
}
