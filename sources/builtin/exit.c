/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 07:40:16 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

static bool	_atoi(char *str, int *num);

int	builtin_exit(char **argv, bool is_subshell)
{
	int	exit_status;

	if (is_subshell == false)
		printf("exit\n");
	if (argv[1] == NULL)
		exit(exit_status_get());
	if (_atoi(argv[1], &exit_status) == false)
	{
		print_error("exit", "Illegal number");
		exit(EXIT_MISUSE_SHELL_BUILTIN);
	}
	exit(exit_status);
}

static bool	_atoi(char *str, int *num)
{
	if (ft_isdigit(*str) == false)
		return (false);
	*num = 0;
	while (ft_isdigit(*str) == true)
	{
		if (ft_is_mul_overflow(*num, 10) == true || \
			ft_is_add_overflow(*num * 10, *str - '0') == true)
			return (false);
		*num = *num * 10 + (*str++ - '0');
	}
	return (*str == '\0');
}
