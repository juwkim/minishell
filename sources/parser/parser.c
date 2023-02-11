/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:55:19 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 08:57:42 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

static bool	parse_command(t_command *command, t_node **cur);

bool	parse(t_list *commands, const t_list *tokens)
{
	t_node		*cur;
	t_command	*command;

	cur = tokens->head->next;
	if (list_init(commands) == false)
		return (print_error(NULL, NULL, NULL));
	while (cur != NULL)
	{
		command = create_command();
		if (command == NULL || \
			parse_command(command, &cur) == false || \
			list_push_back(commands, command) == false)
		{
			destroy_command(command);
			list_destroy(commands, destroy_command);
			return (print_error(NULL, NULL, NULL));
		}
		cur = cur->next;
	}
	return (true);
}

t_command	*create_command(void)
{
	t_command *const	cmd = malloc(sizeof(t_command));

	if (cmd == NULL || list_init(&cmd->argv) == false)
	{
		free(cmd);
		return (NULL);
	}
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->is_in_heredoc = false;
	cmd->is_out_append = false;
	return (cmd);
}

static bool	parse_command(t_command *command, t_node **cur)
{
	const t_token	*token = (*cur)->item;

	if (token->types & (AND | OR | PIPE | O_PARENTHESIS | C_PARENTHESIS))
		return (parse_simple_command(command, token));
	else
		return (parse_complex_command(command, cur));
}

void	destroy_command(void *command)
{
	t_command	*cmd;

	if (command == NULL)
		return ;
	cmd = command;
	if (cmd->type & (GROUP | PIPELINE))
		list_destroy(&cmd->argv, destroy_command);
	else
	{
		free(cmd->in);
		free(cmd->out);
		list_destroy(&cmd->argv, free);
	}
	free(command);
}

char	*get_connected_str(t_node **cur)
{
	t_token	*token;
	t_list	list;
	bool	ret;

	if (list_init(&list) == false)
		return (NULL);
	while (*cur != NULL)
	{
		token = (*cur)->item;
		if (token->types & SINGLE_QUOTE)
			ret = list_push_back(&list, ft_strndup(token->str, token->len));
		else
			ret = list_push_back(&list, \
						expand_env_variable(token->str, token->len));
		if (ret == false)
			return (NULL);
		if ((token->types & CONNECTED) == 0)
			break ;
		*cur = (*cur)->next;
	}
	return (list_strjoin(&list));
}
