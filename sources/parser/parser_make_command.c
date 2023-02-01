/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:12:46 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/01 20:49:08 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

void	make_simple_command(t_command *command, t_deque *tokens, int *cur)
{
	const t_token	*token = get_token(tokens, *cur);

	command->types = token->types;
	list_push_back(&command->argv, ft_strndup(token->str, token->len));
	*cur += 1;
}

void	make_complex_command(t_command *command, t_deque *tokens, int *cur)
{
	t_token	*token;

	command->types = CMD;
	while (*cur != tokens->tail)
	{
		token = get_token(tokens, *cur);
		if (token->types & \
			(TOK_PIPE | TOK_BIN_OP | TOK_O_PARENTHESIS | TOK_C_PARENTHESIS))
			break ;
		if (token->types & TOK_REDIR)
			parse_redirection(command, tokens, cur);
		else
			list_push_back(&command->argv, \
					ft_strndup(token->str, token->len));
		*cur += 1;
	}
}
