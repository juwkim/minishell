/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 06:20:00 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 08:56:22 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/print.h"

static void	print_redirection(const t_command *command);

bool	print_error(const char *program_name, const char *file, \
												const char *message)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	if (program_name != NULL)
	{
		write(STDERR_FILENO, ": ", ft_strlen(": "));
		write(STDERR_FILENO, program_name, ft_strlen(program_name));
	}
	if (file != NULL)
	{
		write(STDERR_FILENO, ": ", ft_strlen(": "));
		write(STDERR_FILENO, file, ft_strlen(file));
	}
	if (message == NULL)
		message = strerror(errno);
	write(STDERR_FILENO, ": ", ft_strlen(": "));
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", ft_strlen("\n"));
	return (false);
}

void	print_tokens(const t_list *tokens)
{
	t_node		*cur;
	t_token		*token;

	cur = tokens->head->next;
	write(STDOUT_FILENO, RED"Token:\t\t\t"DEF_COLOR, 23);
	while (cur->next != NULL)
	{
		token = cur->item;
		write(STDOUT_FILENO, token->str, token->len);
		if (token->types & CONNECTED)
			write(STDOUT_FILENO, GREEN" + "DEF_COLOR, 17);
		else
			write(STDOUT_FILENO, GREEN" : "DEF_COLOR, 17);
		cur = cur->next;
	}
	token = cur->item;
	write(STDOUT_FILENO, token->str, token->len);
	write(STDOUT_FILENO, "\n", 1);
}

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
