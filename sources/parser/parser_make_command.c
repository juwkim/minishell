/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:12:46 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/08 00:20:48 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

void	make_simple_command(t_command *command, const t_token *token)
{
	command->type = token->types;
	list_push_back(&command->argv, ft_strndup(token->str, token->len));
}

void	make_complex_command(t_command *command, t_node **cur)
{
	t_token	*token;

	command->type = CMD;
	while (*cur != NULL)
	{
		token = (*cur)->item;
		if (token->types & \
			(AND | OR | PIPE | O_PARENTHESIS | C_PARENTHESIS))
			break ;
		if (token->types & REDIR)
			parse_redirection(command, cur);
		else
			list_push_back(&command->argv, get_connected_str(cur));
		*cur = (*cur)->next;
	}
}
