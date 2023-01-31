/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:02:07 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/31 03:30:10 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler/signal_handler.h"

void	sigint_handler(int sig)
{
	(void) sig;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_heredoc_handler(int sig)
{
	(void) sig;
	close(STDIN_FILENO);
	write(STDERR_FILENO, "\n", 1);
}
