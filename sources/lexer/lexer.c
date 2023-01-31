/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 04:12:00 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/30 04:16:14 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"

bool	lexical_analyze(t_deque *tokens)
{
	if (bin_pipe_open_analyze(tokens) == false || \
		close_analyze(tokens) == false || \
		text_analyze(tokens) == false || \
		parenthesis_analyze(tokens) == false || \
		redirection_analyze(tokens) == false)
	{
		destroy_tokens(tokens);
		return (false);
	}
	return (true);
}
