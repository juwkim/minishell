/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 04:12:00 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/09 09:48:42 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"

bool	lexical_analyze(t_list *tokens)
{
	if (bin_pipe_open_analyze(tokens) == false || \
		close_analyze(tokens) == false || \
		text_analyze(tokens) == false || \
		parenthesis_analyze(tokens) == false || \
		redirection_analyze(tokens) == false)
	{
		list_destroy(tokens, free);
		return (false);
	}
	return (true);
}
