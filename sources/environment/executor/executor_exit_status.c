/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_exit_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:35:02 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/03 02:38:57 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:29:48 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:54:07 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

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
