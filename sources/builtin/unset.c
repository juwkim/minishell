/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 07:45:32 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

int	builtin_unset(char **argv)
{
	while (*argv)
	{
		if (is_valid_variable_name(*argv) == false)
		{
			print_error(*argv, "bad variable name");
			return (EXIT_MISUSE_SHELL_BUILTIN);
		}
		env_remove(*argv);
		++argv;
	}
	return (EXIT_SUCCESS);
}
