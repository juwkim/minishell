/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 04:12:00 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 07:25:57 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"

int	lexical_analyze(t_list *tokens)
{
	if (bin_pipe_open_analyze(tokens) == EXIT_FAILURE || \
		close_analyze(tokens) == EXIT_FAILURE || \
		text_analyze(tokens) == EXIT_FAILURE || \
		parenthesis_analyze(tokens) == EXIT_FAILURE || \
		redirection_analyze(tokens) == EXIT_FAILURE)
	{
		list_destroy(tokens, free);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
