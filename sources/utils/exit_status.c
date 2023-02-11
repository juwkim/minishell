/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 03:11:41 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 07:28:49 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/exit_status.h"

static int	*exit_status(void);

int	exit_status_get(void)
{
	return (*exit_status());
}

void	exit_status_set(int status)
{
	*exit_status() = status;
}

static int	*exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
}
