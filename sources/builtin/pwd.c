/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:04:40 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 08:59:18 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"

int	builtin_pwd(char **argv)
{
	char	buf[PATH_MAX];

	(void) argv;
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		print_error(NULL, NULL, NULL);
		return (EXIT_FAILURE);
	}
	printf("%s\n", buf);
	return (EXIT_SUCCESS);
}
