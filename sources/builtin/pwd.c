/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 06:18:06 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

void	builtin_pwd(char **argv)
{
	char	buf[PATH_MAX];

	(void) argv;
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		print_error(*argv, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	printf("%s\n", buf);
	exit(EXIT_SUCCESS);
}
