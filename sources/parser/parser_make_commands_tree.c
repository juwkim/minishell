/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_commands_tree.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 06:41:30 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/07 23:25:53 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

static bool	group_merge(t_list *commands);
static void	group_search(const t_list *commands, \
								t_node **start_node, t_node **end_prev_node);

static bool	pipeline_merge(t_list *commands);
static void	pipeline_search(const t_list *commands, \
							t_node **start_prev_node, t_node **end_node);

void	make_commands_tree(t_list *commands)
{
	bool	is_exist_group;
	bool	is_exist_pipeline;

	is_exist_group = true;
	is_exist_pipeline = true;
	print_commands_structure(commands);
	while (is_exist_group || is_exist_pipeline)
	{
		is_exist_group = group_merge(commands);
		if (is_exist_group)
			print_commands_structure(commands);
		is_exist_pipeline = pipeline_merge(commands);
		if (is_exist_pipeline)
			print_commands_structure(commands);
	}
}

static bool	group_merge(t_list *commands)
{
	t_node		*start_node;
	t_node		*end_prev_node;
	t_command	*cmd;

	start_node = NULL;
	end_prev_node = NULL;
	group_search(commands, &start_node, &end_prev_node);
	if (start_node == NULL)
		return (false);
	cmd = start_node->item;
	cmd->types = GROUP;
	free(cmd->argv.head->next->item);
	free(cmd->argv.head->next);
	cmd->argv.head->next = start_node->next;
	start_node->next = end_prev_node->next->next;
	destroy_command(end_prev_node->next->item);
	free(end_prev_node->next);
	end_prev_node->next = NULL;
	return (true);
}

static void	group_search(const t_list *commands, \
							t_node **start_node, t_node **end_prev_node)
{
	t_command	*cmd;
	t_node		*cur;
	t_node		*prev;

	prev = commands->head;
	cur = commands->head->next;
	while (cur != NULL)
	{
		cmd = cur->item;
		if (cmd->types == PIPE)
			*start_node = NULL;
		else if (cmd->types == O_PARENTHESIS)
			*start_node = cur;
		else if (cmd->types == C_PARENTHESIS)
		{
			*end_prev_node = prev;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

static bool	pipeline_merge(t_list *commands)
{
	t_node		*start_prev_node;
	t_node		*end_node;
	t_command	*cmd;

	start_prev_node = NULL;
	end_node = NULL;
	pipeline_search(commands, &start_prev_node, &end_node);
	if (start_prev_node == NULL)
		return (false);
	cmd = create_command();
	cmd->types = PIPELINE;
	cmd->argv.head->next = start_prev_node->next;
	cmd->argv.size = 1;
	start_prev_node->next = list_create_node(cmd);
	start_prev_node->next->next = end_node->next;
	end_node->next = NULL;
	return (true);
}

static void	pipeline_search(const t_list *commands, \
							t_node **start_prev_node, t_node **end_node)
{
	t_node		*cur;
	t_node		*prev;
	const int	flags = (CMD | GROUP | PIPELINE);

	prev = commands->head;
	cur = commands->head->next;
	while (cur->next != NULL && \
			!(((t_command *)cur->item)->types & flags && \
			((t_command *)cur->next->item)->types & PIPE && \
			((t_command *)cur->next->next->item)->types & flags))
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur->next == NULL)
		return ;
	*start_prev_node = prev;
	while (cur->next != NULL && \
			((t_command *)cur->item)->types & flags && \
			((t_command *)cur->next->item)->types & PIPE && \
			((t_command *)cur->next->next->item)->types & flags)
		cur = cur->next->next;
	*end_node = cur;
}
