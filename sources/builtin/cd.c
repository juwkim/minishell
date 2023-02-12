/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 08:41:08 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

static const char	*get_dir(char **argv);
static int			update_pwd(void);

void	builtin_cd(char **argv)
{
	const char	*dir = get_dir(argv);

	if (dir == NULL)
		exit(EXIT_FAILURE);
	if (chdir(dir) == -1)
	{
		print_error("cd", dir, NULL);
		exit(EXIT_FAILURE);
	}
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
		printf("%s\n", dir);
	exit(update_pwd());
}

static const char	*get_dir(char **argv)
{
	const char	*dir;

	dir = NULL;
	if (argv[1] == NULL)
	{
		dir = env_get("HOME");
		if (dir == NULL)
			print_error("cd", NULL, "HOME not set");
	}
	else if (argv[1] && ft_strncmp(argv[1], "-", 1) == 0)
	{
		dir = env_get("OLDPWD");
		if (dir == NULL)
			print_error("cd", NULL, "OLDPWD not set");
	}
	else
		dir = argv[1];
	return (dir);
}

static int	update_pwd(void)
{
	char	buf[PATH_MAX];
	char	*pwd;

	pwd = env_get("PWD");
	if (pwd == NULL)
	{
		env_remove("OLDPWD");
		return (EXIT_SUCCESS);
	}
	if (getcwd(buf, sizeof(buf)) == NULL || \
		env_set("OLDPWD", pwd) == EXIT_FAILURE || \
		env_set("PWD", buf) == EXIT_FAILURE)
		return (print_error("cd", "update_pwd", NULL));
	return (EXIT_SUCCESS);
}
