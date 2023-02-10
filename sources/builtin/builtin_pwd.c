/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/10 11:18:51 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

int	builtin_pwd(char **argv)
{
	char	buf[PATH_MAX];

	(void) argv;
	if (getcwd(buf, sizeof(buf)))
	{
		printf("%s\n", buf);
		return (EXIT_SUCCESS);
	}
	else
	{
		print_error(NULL, NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
}
