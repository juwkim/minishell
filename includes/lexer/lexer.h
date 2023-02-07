/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 04:12:19 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/07 23:50:14 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "global.h"
# include "tokenizer/tokenizer.h"

# define ERR_SYNTAX "syntax error near unexpected token"

// lexer.c
bool	lexical_analyze(t_list *tokens);

// lexer_utils.c
bool	bin_pipe_open_analyze(const t_list *tokens);
bool	close_analyze(const t_list *tokens);
bool	text_analyze(const t_list *tokens);
bool	parenthesis_analyze(const t_list *tokens);
bool	redirection_analyze(const t_list *tokens);

#endif // LEXER_H
