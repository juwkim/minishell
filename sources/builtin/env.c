/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 04:53:01 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

void	builtin_env(char **argv)
{
	int	i;

	(void) argv;
	i = 0;
	while (i < g_env.count)
	{
		printf("%s\n", g_env.item[i]);
		++i;
	}
	++argv;
	while (*argv)
	{
		printf("%s\n", *argv);
		++argv;
	}
	exit(EXIT_SUCCESS);
}
