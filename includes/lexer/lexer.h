/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 04:12:19 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 07:04:43 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "global.h"
# include "utils/print.h"

# define ERR_SYNTAX "syntax error near unexpected token"

// lexer.c
bool	lexical_analyze(t_list *tokens);

// utils.c
bool	bin_pipe_open_analyze(const t_list *tokens);
bool	close_analyze(const t_list *tokens);
bool	text_analyze(const t_list *tokens);
bool	parenthesis_analyze(const t_list *tokens);
bool	redirection_analyze(const t_list *tokens);

#endif // LEXER_H
