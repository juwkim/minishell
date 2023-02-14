/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 04:12:19 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/14 11:03:34 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "global.h"
# include "utils/print.h"
# include "utils/exit_status.h"

# define ERR_SYNTAX "syntax error near unexpected token"

// lexer.c
int	lexical_analyze(t_list *tokens);

// utils.c
int	bin_pipe_open_analyze(const t_list *tokens);
int	close_analyze(const t_list *tokens);
int	text_analyze(const t_list *tokens);
int	parenthesis_analyze(const t_list *tokens);
int	redirection_analyze(const t_list *tokens);

#endif // LEXER_H
