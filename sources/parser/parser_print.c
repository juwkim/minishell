/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:39:03 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/31 00:44:23 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

void	print_commands(t_deque *commands)
{
	int			cur;
	t_command	*command;

	cur = commands->head;
	while (cur != commands->tail)
	{
		command = get_command(commands, cur);
		if (command->types & TOK_BIN_OP)
			printf("types: BIN_OP\n");
		else if (command->types & TOK_PIPE)
			printf("types: PIPE\n");
		else if (command->types & TOK_O_PARENTHESIS)
			printf("types: O_PARENTHESIS\n");
		else if (command->types & TOK_C_PARENTHESIS)
			printf("types: C_PARENTHESIS\n");
		else
			printf("types: CMD\n");
		list_print(&command->argv);
		printf("Redirection IN: %s\n", command->in);
		printf("Redirection OUT: %s\n", command->out);
		printf("Redirection OUPAPP: %s\n", command->outapp);
		printf("Redirection ERR: %s\n", command->err);
		cur = (cur + 1) % QUEUE_SIZE;
	}
}
