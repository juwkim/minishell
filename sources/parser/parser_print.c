/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:39:03 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/08 00:20:48 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

static void	print_redirection(const t_command *command);

void	print_commands(const t_list *commands)
{
	t_node		*cur;
	t_command	*command;

	cur = commands->head->next;
	printf(RED"Commands:\t\t"DEF_COLOR);
	while (cur != NULL)
	{
		command = cur->item;
		if (list_is_empty(&command->argv))
			break ;
		if (command->type & (O_PARENTHESIS | C_PARENTHESIS))
			printf(CYAN"%s "DEF_COLOR, (char *) list_front(&command->argv));
		else if (command->type & (AND | OR))
			printf(MAGENTA"%s "DEF_COLOR, (char *) list_front(&command->argv));
		else if (command->type & PIPE)
			printf(BLUE"%s "DEF_COLOR, (char *) list_front(&command->argv));
		else
		{
			list_print(&command->argv);
			print_redirection(command);
		}
		cur = cur->next;
	}
	printf("\n");
}

static void	print_redirection(const t_command *command)
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

void	print_commands_structure(const t_list *commands)
{
	t_node		*cur;
	t_command	*command;

	cur = commands->head->next;
	printf(RED"Commands Structure:\t"DEF_COLOR);
	while (cur != NULL)
	{
		command = cur->item;
		if (list_is_empty(&command->argv))
			break ;
		if (command->type & (O_PARENTHESIS | C_PARENTHESIS))
			printf(CYAN"%s "DEF_COLOR, (char *) list_front(&command->argv));
		else if (command->type & (AND | OR))
			printf(MAGENTA"%s "DEF_COLOR, (char *) list_front(&command->argv));
		else if (command->type & PIPE)
			printf(BLUE"%s "DEF_COLOR, (char *) list_front(&command->argv));
		else if (command->type & GROUP)
			printf(YELLOW"GR "DEF_COLOR);
		else if (command->type & PIPELINE)
			printf(YELLOW"PL "DEF_COLOR);
		else
			printf(YELLOW"CMD "DEF_COLOR);
		cur = cur->next;
	}
	printf("\n");
}
