/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 04:05:10 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 06:12:03 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"

int	bin_pipe_open_analyze(const t_list *tokens)
{
	bool		prev_bin_pipe_open;
	const int	bin_pipe_open = AND | OR | PIPE | O_PARENTHESIS;
	const int	bin_pipe_close = AND | OR | PIPE | C_PARENTHESIS;
	t_node		*cur;
	t_token		*token;

	token = NULL;
	prev_bin_pipe_open = true;
	cur = tokens->head->next;
	while (cur != NULL)
	{
		token = cur->item;
		if (prev_bin_pipe_open == true && (token->types & bin_pipe_close))
		{
			*(token->str + token->len) = '\0';
			return (print_error(ERR_SYNTAX, NULL, token->str));
		}
		prev_bin_pipe_open = (token->types & bin_pipe_open) != 0;
		cur = cur->next;
	}
	if (prev_bin_pipe_open == false)
		return (EXIT_SUCCESS);
	*(token->str + token->len) = '\0';
	return (print_error(ERR_SYNTAX, NULL, token->str));
}

int	close_analyze(const t_list *tokens)
{
	const int	text_redir_open = TEXT | REDIR | O_PARENTHESIS;
	t_node		*cur;
	t_token		*token;

	cur = tokens->head->next;
	while (cur->next != NULL)
	{
		token = cur->item;
		if ((token->types & C_PARENTHESIS) && \
			(((t_token *)(cur->next->item))->types & text_redir_open))
		{
			*(token->str + token->len) = '\0';
			return (print_error(ERR_SYNTAX, NULL, token->str));
		}
		cur = cur->next;
	}
	return (EXIT_SUCCESS);
}

int	text_analyze(const t_list *tokens)
{
	t_node		*cur;
	t_token		*token;

	cur = tokens->head->next;
	while (cur->next != NULL)
	{
		token = cur->item;
		if ((token->types & TEXT) && \
			((t_token *)(cur->next->item))->types & O_PARENTHESIS)
		{
			*(token->str + token->len) = '\0';
			return (print_error(ERR_SYNTAX, NULL, token->str));
		}
		cur = cur->next;
	}
	return (EXIT_SUCCESS);
}

int	parenthesis_analyze(const t_list *tokens)
{
	int			opened;
	t_node		*cur;
	t_token		*token;

	opened = 0;
	cur = tokens->head->next;
	while (cur != NULL)
	{
		token = cur->item;
		if (token->types & O_PARENTHESIS)
			++opened;
		if (token->types & C_PARENTHESIS)
			--opened;
		if (opened < 0)
			break ;
		cur = cur->next;
	}
	if (opened != 0)
	{
		*(token->str + token->len) = '\0';
		return (print_error(ERR_SYNTAX, NULL, token->str));
	}
	return (EXIT_SUCCESS);
}

int	redirection_analyze(const t_list *tokens)
{
	bool		prev_redirection;
	t_node		*cur;
	t_token		*token;

	prev_redirection = false;
	cur = tokens->head->next;
	while (cur != NULL)
	{
		token = cur->item;
		if (prev_redirection == true)
		{
			if ((token->types & TEXT) == 0 || \
				(token->types & O_PARENTHESIS))
			{
				*(token->str + token->len) = '\0';
				return (print_error(ERR_SYNTAX, NULL, token->str));
			}
		}
		prev_redirection = (((t_token *)(cur->item))->types & REDIR) != 0;
		cur = cur->next;
	}
	if (prev_redirection == true)
		return (print_error(ERR_SYNTAX, NULL, "\'newline\'"));
	return (EXIT_SUCCESS);
}
