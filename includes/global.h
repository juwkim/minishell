/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:01:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 07:05:53 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include "linked_list.h"

# define PROMPT 	"minishell$ "

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

# define AND			4096
# define OR				8192

# define CMD			16384
# define GROUP			32768
# define PIPELINE		65536

# define MAX_TABLE_SIZE 24593

typedef struct s_env
{
	char	*item[MAX_TABLE_SIZE];
	int		count;
}	t_env;

typedef struct s_token
{
	char	*str;
	int		len;
	int		types;
}	t_token;

typedef struct s_command
{
	int		type;
	t_list	argv;
	char	*in;
	char	*out;
	bool	is_in_heredoc;
	bool	is_out_append;
}	t_command;

extern t_env	g_env;

#endif // GLOBAL_H
