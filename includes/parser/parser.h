/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:56:01 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/08 06:14:44 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "global.h"
# include "signal_handler/signal_handler.h"
# include "tokenizer/tokenizer.h"
# include "expander/expander.h"

// parser.c
bool		parse(t_list *commands, const t_list *tokens);
t_command	*create_command(void);
void		destroy_command(void *command);
char		*get_connected_str(t_node **cur);
t_command	*get_command(t_list *commands, t_node *cur);

// parser_make_command.c
void		make_simple_command(t_command *command, const t_token *token);
void		make_complex_command(t_command *command, t_node **cur);

// parser_redirection.c
void		parse_redirection(t_command *command, t_node **cur);

// parser_print.c
void		print_commands(const t_list *commands);
void		print_commands_structure(const t_list *commands);

// parser_make_commands_tree
void		make_commands_tree(t_list *commands);

#endif // PARSER_H
