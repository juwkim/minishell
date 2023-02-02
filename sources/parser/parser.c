/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:55:19 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/03 01:08:39 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

static t_command	*init_command(void);

bool	parse(t_deque *commands, t_deque *tokens)
{
	int			cur;
	t_command	*command;
	t_token		*token;

	cur = 0;
	dq_init(commands);
	while (cur != tokens->tail)
	{
		command = init_command();
		if (command == NULL)
		{
			destroy_commands(commands);
			return (false);
		}
		token = get_token(tokens, cur);
		if (token->types & \
			(TOK_PIPE | TOK_BIN_OP | TOK_O_PARENTHESIS | TOK_C_PARENTHESIS))
			make_simple_command(command, tokens, &cur);
		else
			make_complex_command(command, tokens, &cur);
		dq_push_back(commands, command);
	}
	return (true);
}

static t_command	*init_command(void)
{
	t_command *const	cmd = malloc(sizeof(t_command));

	if (cmd == NULL)
	{
		print_error(NULL, NULL, strerror(ENOMEM));
		return (NULL);
	}
	list_init(&cmd->argv);
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->is_in_heredoc = false;
	cmd->is_out_append = false;
	return (cmd);
}

void	destroy_commands(t_deque *commands)
{
	int			cur;
	t_command	*command;

	cur = commands->head;
	while (cur != commands->tail)
	{
		command = get_command(commands, cur);
		list_destroy(&command->argv);
		free(command->in);
		free(command->out);
		free(command);
		cur = (cur + 1) % QUEUE_SIZE;
	}
}

t_command	*get_command(t_deque *commands, int cur)
{
	return ((t_command *) commands->items[cur]);
}

void	remove_comma(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (true)
	{
		while (str[i] != '\0' && (str[i] == '\'' || str[i] == '\"'))
			++i;
		if (str[i] == '\0')
			break ;
		str[j] = str[i];
		++i;
		++j;
	}
	str[j] = '\0';
}
