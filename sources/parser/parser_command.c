/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:12:46 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/09 10:46:33 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

bool	parse_simple_command(t_command *command, const t_token *token)
{
	command->type = token->types;
	return (list_push_back(&command->argv, ft_strndup(token->str, token->len)));
}

bool	parse_complex_command(t_command *command, t_node **cur)
{
	t_token		*token;
	const int	flags = (AND | OR | PIPE | O_PARENTHESIS | C_PARENTHESIS);

	command->type = CMD;
	token = (*cur)->item;
	while (true)
	{
		if (token->types & REDIR)
		{
			if (parse_redirection(command, cur) == false)
				return (false);
		}
		else
		{
			if (list_push_back(&command->argv, get_connected_str(cur)) == false)
				return (false);
		}
		if ((*cur)->next == NULL || \
			((t_token *)(*cur)->next->item)->types & flags)
			break ;
		*cur = (*cur)->next;
	}
	return (true);
}
