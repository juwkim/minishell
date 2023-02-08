/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:55:19 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/08 15:59:03 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

bool	parse(t_list *commands, const t_list *tokens)
{
	t_node		*cur;
	t_token		*token;
	t_command	*command;

	cur = tokens->head->next;
	list_init(commands);
	while (cur != NULL)
	{
		command = create_command();
		if (command == NULL)
		{
			list_destroy(commands, destroy_command);
			return (false);
		}
		token = cur->item;
		if (token->types & (AND | OR | PIPE | O_PARENTHESIS | C_PARENTHESIS))
		{
			make_simple_command(command, token);
			cur = cur->next;
		}
		else
			make_complex_command(command, &cur);
		list_push_back(commands, command);
	}
	return (true);
}

t_command	*create_command(void)
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

void	destroy_command(void *command)
{
	t_command	*cmd;

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

	list_init(&list);
	while (*cur != NULL)
	{
		token = (*cur)->item;
		if (token->types & SINGLE_QUOTE)
			list_push_back(&list, ft_strndup(token->str, token->len));
		else
			list_push_back(&list, expand_env_variable(token->str, token->len));
		if ((token->types & CONNECTED) == 0)
			break ;
		*cur = (*cur)->next;
	}
	return (list_strjoin(&list));
}
