/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:56:01 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/14 10:54:57 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "global.h"
# include "expander/expander.h"
# include "executor/executor.h"

# define MEMORY_ALLOCATE_FAIL 2

// parser.c
int			parse(t_list *commands, t_list *tokens);
t_command	*create_command(void);
void		destroy_command(void *command);
char		*get_connected_str(t_node **cur);
t_command	*get_command(t_list *commands, t_node *cur);

// command.c
int			parse_simple_command(t_command *command, const t_token *token);
int			parse_complex_command(t_command *command, t_node **cur);

// redirection.c
int			parse_redirection(t_command *command, t_node **cur);
char		*parse_heredoc(char *delimiter);

// make_commands_tree
int			make_commands_tree(t_list *commands);

#endif // PARSER_H
