/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:01:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/06 15:54:59 by juwkim           ###   ########.fr       */
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
# define PIPE			2
# define SINGLE_QUOTE	4
# define DOUBLE_QUOTE	8
# define CONNECTED		16

# define O_PARENTHESIS	32
# define C_PARENTHESIS	64

# define REDIR			128
# define REDIR_OUT		256
# define REDIR_OUT_APP	512
# define REDIR_IN		1024
# define REDIR_HEREDOC	2048

# define CMD			4096

# define AND			8192
# define OR				16384
# define SCMD			32768
# define GROUP			65536
# define PIPELINE		131072

extern t_hash_table	g_env;

#endif // GLOBAL_H
