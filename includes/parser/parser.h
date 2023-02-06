/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:56:01 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/06 09:11:51 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "global.h"
# include "signal_handler/signal_handler.h"
# include "tokenizer/tokenizer.h"
# include "expander/expander.h"

typedef struct s_command
{
	int				types;
	t_linked_list	argv;
	char			*in;
	char			*out;
	bool			is_in_heredoc;
	bool			is_out_append;
}	t_command;

typedef struct s_commands_tree
{
	int						type;
	t_linked_list			cmd_list;
	struct s_commands_tree	*next;
}	t_commands_tree;

// parser.c
bool		parse(t_deque *commands, t_deque *tokens);
void		destroy_commands(t_deque *commands);
char		*get_connected_str(t_deque *tokens, int *cur);
t_command	*get_command(t_deque *commands, int cur);

// parser_make_command.c
void		make_simple_command(t_command *command, t_deque *tokens, int *cur);
void		make_complex_command(t_command *command, t_deque *tokens, int *cur);

// parser_redirection.c
void		parse_redirection(t_command *command, t_deque *tokens, int *cur);

// parser_print.c
void		print_commands(t_deque *commands);
void		print_commands_structure(t_deque *commands);

// parser_make_commands_tree.c
bool		make_commands_tree(t_linked_list *commands_tree, t_deque *commands);

#endif // PARSER_H
