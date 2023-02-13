/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/13 09:55:36 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

int	builtin_unset(char **argv)
{
	while (*argv)
	{
		if (is_valid_variable_name(*argv) == false)
		{
			print_error(*argv, NULL, "not a valid identifier");
			return (EXIT_FAILURE);
		}
		env_remove(*argv);
		++argv;
	}
	return (EXIT_SUCCESS);
}
