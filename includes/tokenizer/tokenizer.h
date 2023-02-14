/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:25:43 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/14 10:58:48 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "global.h"
# include "lexer/lexer.h"

// tokenizer.c
int	tokenize(t_list *tokens, const char *input);

// utils.c
int	is_bin_operator_or_pipe(const char *input, int *idx, t_token *token);
int	is_parenthesis(const char *input, int *idx, t_token *token);
int	is_redirection(const char *input, int *idx, t_token *token);
int	is_text(const char *input, int *idx, t_token *token);
int	is_quote(const char *input, int *idx, t_token *token);

#endif // TOKENIZER_H
