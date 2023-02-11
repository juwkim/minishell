/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 06:35:50 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

void	builtin_unset(char **argv)
{
	while (*argv)
	{
		if (is_valid_variable_name(*argv) == false)
		{
			print_error(*argv, NULL, "not a valid identifier");
			exit(EXIT_FAILURE);
		}
		env_remove(*argv);
		++argv;
	}
	exit(EXIT_SUCCESS);
}
