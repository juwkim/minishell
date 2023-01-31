/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 04:12:19 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/30 04:09:36 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "global.h"
# include "tokenizer/tokenizer.h"

# define ERR_SYNTAX "syntax error near unexpected token"

// lexer.c
bool	lexical_analyze(t_deque *tokens);

// lexer_utils.c
bool	bin_pipe_open_analyze(t_deque *tokens);
bool	close_analyze(t_deque *tokens);
bool	text_analyze(t_deque *tokens);
bool	parenthesis_analyze(t_deque *tokens);
bool	redirection_analyze(t_deque *tokens);

#endif // LEXER_H
