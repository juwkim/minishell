/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:25:43 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 07:34:00 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "global.h"
# include "lexer/lexer.h"

// tokenizer.c
int		tokenize(t_list *tokens, const char *input);

// utils.c
bool	is_bin_operator_or_pipe(const char *input, int *idx, t_token *token);
bool	is_parenthesis(const char *input, int *idx, t_token *token);
bool	is_redirection(const char *input, int *idx, t_token *token);
bool	is_text(const char *input, int *idx, t_token *token);
bool	is_quote(const char *input, int *idx, t_token *token);

#endif // TOKENIZER_H
