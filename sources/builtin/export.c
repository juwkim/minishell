/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 08:10:49 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

static int	_env(void);

int	builtin_export(char **argv)
{
	char	*equal_sign;

	++argv;
	if (*argv == NULL)
		return (_env());
	while (*argv)
	{
		if (is_valid_variable_name(*argv) == false)
		{
			print_error(*argv, "bad variable name");
			return (EXIT_MISUSE_SHELL_BUILTIN);
		}
		equal_sign = ft_strchr(*argv, '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			if (env_set(*argv, equal_sign + 1) == false)
				return (EXIT_FAILURE);
		}
		++argv;
	}
	return (EXIT_SUCCESS);
}

static int	_env(void)
{
	int	i;

	i = 0;
	while (i < g_env.count)
	{
		printf("export %s\n", g_env.item[i]);
		++i;
	}
	return (EXIT_SUCCESS);
}
