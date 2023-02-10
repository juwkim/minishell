/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:01:43 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 07:05:21 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <stdio.h>
# include <signal.h>

# include "../../../readline/readline.h"
# include "global.h"

void	sigint_handler(int sig);
void	sigint_heredoc_handler(int sig);

#endif // SIGNAL_HANDLER_H
