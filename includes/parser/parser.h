/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:56:01 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/03 06:13:38 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "global.h"
# include "signal_handler/signal_handler.h"
# include "tokenizer/tokenizer.h"
# include "expander/expander.h"

# define CMD			1
# define CMD_AND		2
# define CMD_OR			4
# define CMD_PIPE		8
# define CMD_PIPELINE	64
# define CMD_GROUP		128
# define CMD_L_SCMD		256
# define CMD_L_CMD		512

typedef struct s_command
{
	int				types;
	t_linked_list	argv;
	char			*in;
	char			*out;
	bool			is_in_heredoc;
	bool			is_out_append;
}	t_command;

// parser.c
bool		parse(t_deque *commands, t_deque *tokens);
void		destroy_commands(t_deque *commands);
char		*get_connected_str(t_deque *tokens, int *cur);

// parser_make_command.c
void		make_simple_command(t_command *command, t_deque *tokens, int *cur);
void		make_complex_command(t_command *command, t_deque *tokens, int *cur);

// parser_redirection.c
void		parse_redirection(t_command *command, t_deque *tokens, int *cur);

// parser_print.c
void		print_commands(t_deque *commands);

#endif // PARSER_H
