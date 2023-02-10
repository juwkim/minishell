/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 05:38:13 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

int	builtin_echo(char **argv)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		i = 2;
		newline = false;
	}
	if (argv[i])
	{
		while (argv[i + 1])
		{
			printf("%s ", argv[i]);
			++i;
		}
		printf("%s", argv[i]);
	}
	if (newline)
		printf("\n");
	return (EXIT_SUCCESS);
}
