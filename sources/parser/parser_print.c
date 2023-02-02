/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:39:03 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/03 05:57:06 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

static void	print_redirection(t_command *command);

void	print_commands(t_deque *commands)
{
	int			cur;
	t_command	*command;

	cur = commands->head;
	printf(RED"Parsing:\t\t"DEF_COLOR);
	while (cur != commands->tail)
	{
		command = commands->items[cur];
		if (command->types & (TOK_O_PARENTHESIS | TOK_C_PARENTHESIS))
			printf(CYAN"%s "DEF_COLOR, list_front(&command->argv));
		else if (command->types & TOK_BIN_OP)
			printf(MAGENTA"%s "DEF_COLOR, list_front(&command->argv));
		else if (command->types & TOK_PIPE)
			printf(BLUE"%s "DEF_COLOR, list_front(&command->argv));
		else
		{
			list_print(&command->argv);
			print_redirection(command);
		}
		cur = (cur + 1) % QUEUE_SIZE;
	}
	printf("\n");
}

static void	print_redirection(t_command *command)
{
	if (command->in)
	{
		if (command->is_in_heredoc)
			printf(WHITE"<< "BLUE"%s "DEF_COLOR, command->in);
		else
			printf(WHITE"< "BLUE"%s "DEF_COLOR, command->in);
	}
	if (command->out)
	{
		if (command->is_out_append)
			printf(WHITE">> "BLUE"%s "DEF_COLOR, command->out);
		else
			printf(WHITE"> "BLUE"%s "DEF_COLOR, command->out);
	}
}
