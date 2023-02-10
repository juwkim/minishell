/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/10 16:44:23 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

// static char	*get_dir(int argc, char **argv);
// static bool	update_pwd(void);

int	builtin_cd(char **argv)
{
	// char	*dir;
	// int		argc;

	// argc = 0;
	// while (argv[argc])
	// 	++argc;
	// dir = get_dir(argc, argv);
	// if (dir == NULL)
	// 	return (EXIT_FAILURE);
	// if (chdir(dir) == NULL)
	// {
	// 	print_error(NULL, NULL, strerror(errno));
	// 	return (EXIT_FAILURE);
	// }
	// if (argv[1] && ft_strncmp(argv[1], "-", 1) == 0)
	// 	printf("%s\n", dir);
	// if (update_pwd() == false)
	// 	return (EXIT_FAILURE);
	(void) argv;
	return (EXIT_SUCCESS);
}

// static char	*get_dir(int argc, char **argv)
// {
// 	char	*dir;

// 	dir = NULL;
// 	if (argc == 1)
// 	{
// 		dir = env_get("HOME");
// 		if (dir == NULL)
// 			print_error(NULL, NULL, strerror(errno));
// 	}
// 	else if (argv[1] && ft_strncmp(argv[1], "-", 1) == 0)
// 	{
// 		dir = env_get("OLDPWD");
// 		if (dir == NULL)
// 			print_error(NULL, NULL, strerror(errno));
// 	}
// 	else
// 		dir = argv[1];
// 	return (dir);
// }

// static bool	update_pwd(void)
// {
// 	char	buf[PATH_MAX];
// 	char	*pwd;
// 	char	*oldpwd;

// 	pwd = env_get("PWD");
// 	if (pwd)
// 	{
// 		if (getcwd(buf, sizeof(buf)) == NULL)
// 		{
// 			print_error(NULL, NULL, strerror(errno));
// 			return (false);
// 		}
// 		env_set("OLDPWD", pwd);
// 		env_set("PWD", buf);
// 	}
// 	else
// 		env_remove("OLDPWD");
// }
