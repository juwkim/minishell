/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 04:05:10 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/31 01:14:31 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"

bool	bin_pipe_open_analyze(t_deque *tokens)
{
	int			cur;
	bool		prev_bin_pipe_open;
	const int	bin_pipe_open = TOK_BIN_OP | TOK_PIPE | TOK_O_PARENTHESIS;
	const int	bin_pipe_close = TOK_BIN_OP | TOK_PIPE | TOK_C_PARENTHESIS;
	t_token		*token;

	token = NULL;
	prev_bin_pipe_open = true;
	cur = tokens->head;
	while (cur != tokens->tail)
	{
		token = get_token(tokens, cur);
		if (prev_bin_pipe_open == true && (token->types & bin_pipe_close))
		{
			token = get_token(tokens, cur - 1);
			*(token->str + token->len) = '\0';
			return (print_error(ERR_SYNTAX, NULL, token->str));
		}
		prev_bin_pipe_open = (token->types & bin_pipe_open) != 0;
		cur = (cur + 1) % QUEUE_SIZE;
	}
	if (prev_bin_pipe_open == false)
		return (true);
	*(token->str + token->len) = '\0';
	return (print_error(ERR_SYNTAX, NULL, token->str));
}

bool	close_analyze(t_deque *tokens)
{
	int			cur;
	const int	text_redir_open = TOK_TEXT | TOK_REDIR | TOK_O_PARENTHESIS;
	t_token		*token;

	cur = tokens->head;
	while (cur != tokens->tail - 1)
	{
		token = get_token(tokens, cur);
		if ((token->types & TOK_C_PARENTHESIS) && \
			(get_token(tokens, cur + 1)->types & text_redir_open))
		{
			*(token->str + token->len) = '\0';
			return (print_error(ERR_SYNTAX, NULL, token->str));
		}
		cur = (cur + 1) % QUEUE_SIZE;
	}
	return (true);
}

bool	text_analyze(t_deque *tokens)
{
	int			cur;
	t_token		*token;

	cur = tokens->head;
	while (cur != tokens->tail - 1)
	{
		token = get_token(tokens, cur);
		if ((token->types & TOK_TEXT) && \
			(get_token(tokens, cur + 1)->types & TOK_O_PARENTHESIS))
		{
			*(token->str + token->len) = '\0';
			return (print_error(ERR_SYNTAX, NULL, token->str));
		}
		cur = (cur + 1) % QUEUE_SIZE;
	}
	return (true);
}

bool	parenthesis_analyze(t_deque *tokens)
{
	int			cur;
	int			opened;
	t_token		*token;

	cur = tokens->head;
	opened = 0;
	while (cur != tokens->tail)
	{
		token = get_token(tokens, cur);
		if (token->types & TOK_O_PARENTHESIS)
			++opened;
		if (token->types & TOK_C_PARENTHESIS)
			--opened;
		if (opened < 0)
			break ;
		cur = (cur + 1) % QUEUE_SIZE;
	}
	if (opened != 0)
	{
		*(token->str + token->len) = '\0';
		return (print_error(ERR_SYNTAX, NULL, token->str));
	}
	return (true);
}

bool	redirection_analyze(t_deque *tokens)
{
	int			cur;
	bool		prev_redirection;
	t_token		*token;

	prev_redirection = false;
	cur = tokens->head;
	while (cur != tokens->tail)
	{
		token = get_token(tokens, cur);
		if (prev_redirection == true)
		{
			if ((token->types & TOK_TEXT) == 0 || \
				(token->types & TOK_O_PARENTHESIS))
			{
				token = get_token(tokens, cur - 1);
				*(token->str + token->len) = '\0';
				return (print_error(ERR_SYNTAX, NULL, token->str));
			}
		}
		prev_redirection = (get_token(tokens, cur)->types & TOK_REDIR) != 0;
		cur = (cur + 1) % QUEUE_SIZE;
	}
	if (prev_redirection == true)
		return (print_error(ERR_SYNTAX, NULL, "\'newline\'"));
	return (true);
}
