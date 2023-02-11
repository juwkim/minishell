/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 06:37:46 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

static void	_env(void);

void	builtin_export(char **argv)
{
	char	*equal_sign;

	++argv;
	if (*argv == NULL)
		_env();
	while (*argv)
	{
		if (is_valid_variable_name(*argv) == false)
		{
			print_error("export", *argv, "not a valid identifier");
			exit(EXIT_FAILURE);
		}
		equal_sign = ft_strchr(*argv, '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			if (env_set(*argv, equal_sign + 1) == EXIT_FAILURE)
				exit(EXIT_FAILURE);
		}
		++argv;
	}
	exit(EXIT_SUCCESS);
}

static void	_env(void)
{
	int	i;

	i = 0;
	while (i < g_env.count)
	{
		printf("export %s\n", g_env.item[i]);
		++i;
	}
	exit(EXIT_SUCCESS);
}
