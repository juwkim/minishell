/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:35:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/04 07:36:12 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "global.h"
# include "parser/parser.h"

// executor.c
int		execute(t_deque *commands, int start, int end, bool is_subshell);

// executor_exit_status.c
int		exit_status_get(void);
void	exit_status_set(int status);

// executor_operator_skip.c
int		get_operator_skipped_idx(t_deque *commands, int idx);
bool	is_operator_skip(int command_type);

#endif // EXECUTOR_H
