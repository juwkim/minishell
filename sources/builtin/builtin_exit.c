/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/10 16:44:32 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

static bool	num_is_numeric(char *str);

int	builtin_exit(char **argv, bool is_subshell)
{
	int	argc;
	int	exit_status;

	if (is_subshell == false)
		write(STDERR_FILENO, "exit\n", 5);
	argc = 0;
	while (argv[argc])
		++argc;
	exit_status = exit_status_get();
	if (argc >= 2 && num_is_numeric(argv[1]) == false)
		exit_status = 255;
	else if (argc == 2)
		exit_status = ft_atoi(argv[1]);
	else if (argc > 2)
	{
		print_error(NULL, NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
	exit (exit_status);
}

static bool	num_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
	{
		print_error(NULL, NULL, strerror(errno));
		return (false);
	}
	else if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
		++i;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
		{
			print_error(NULL, NULL, strerror(errno));
			return (false);
		}
		++i;
	}
	return (true);
}
