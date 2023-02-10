/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 07:07:14 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

// static void	print_vars(void);
static bool	is_valid_argument(const char *const arg);

int	builtin_export(char **argv)
{
	int	i;
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (argv[1] == NULL)
	{
		// print_vars();
		return (exit_status);
	}
	i = 1;
	while (argv[i])
	{
		if (is_valid_argument(argv[i]) == false)
		{
			print_error(NULL, NULL);
			exit_status = EXIT_FAILURE;
		}
		// else if (ft_strchr(argv[i], '='))
		// 	env_set(argv[i]);
		++i;
	}
	return (exit_status);
}

static bool	is_valid_argument(const char *const arg)
{
	int	i;

	if (arg[0] == '\0' || arg[0] == '=')
		return (false);
	i = 0;
	// while (arg[i] != '\0' && arg[i] != '=' && env_is_var_char(arg[i]))
	// 	i++;
	if (arg[i] == '\0' || arg[i] == '=')
		return (true);
	else
		return (false);
}
