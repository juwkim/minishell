/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:01:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/04 05:52:08 by juwkim           ###   ########.fr       */
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
# include "hash_table.h"
# include "linked_list.h"
# include "utils/error.h"

# define PROMPT 	"minishell$ "
# define SHELL_NAME	"minishell"

# define DEF_COLOR	"\033[0;39m"
# define GRAY		"\033[1;90m"
# define RED		"\033[1;91m"
# define GREEN		"\033[1;92m"
# define YELLOW		"\033[1;93m"
# define BLUE		"\033[1;94m"
# define MAGENTA	"\033[1;95m"
# define CYAN		"\033[1;96m"
# define WHITE		"\033[1;97m"

# define TEXT			1
# define AND			2
# define OR				4
# define PIPE			8
# define SINGLE_QUOTE	16
# define DOUBLE_QUOTE	32
# define CONNECTED		64

# define O_PARENTHESIS	128
# define C_PARENTHESIS	256

# define REDIR			512
# define REDIR_OUT		1024
# define REDIR_OUT_APP	2048
# define REDIR_IN		4096
# define REDIR_HEREDOC	8192

# define CMD			16384

extern t_hash_table	g_env;

#endif // GLOBAL_H
