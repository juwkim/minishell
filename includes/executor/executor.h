/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:35:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/07 07:14:45 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "global.h"
# include "parser/parser.h"

// executor.c
int		execute(t_list *commands, int start, int end, bool is_subshell);

// executor_exit_status.c
int		exit_status_get(void);
void	exit_status_set(int status);

#endif // EXECUTOR_H
