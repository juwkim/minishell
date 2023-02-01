/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:01:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/01 20:44:04 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <errno.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>

# include "libft.h"
# include "deque.h"
# include "linked_list.h"
# include "utils/error.h"

# define PROMPT 	"minishell$ "
# define SHELL_NAME	"minishell"

extern t_deque	g_env;

#endif // GLOBAL_H
