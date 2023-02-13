/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/13 09:55:10 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

int	builtin_echo(char **argv)
{
	bool	newline;

	newline = true;
	++argv;
	if (*argv && ft_strcmp(*argv, "-n") == 0)
	{
		++argv;
		newline = false;
	}
	if (*argv)
	{
		while (*(argv + 1))
		{
			printf("%s ", *argv);
			++argv;
		}
		printf("%s", *argv);
	}
	if (newline)
		printf("\n");
	return (EXIT_SUCCESS);
}
