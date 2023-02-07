/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 03:25:15 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/07 23:44:57 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer/tokenizer.h"

bool	is_bin_operator_or_pipe(const char *input, int *idx, t_token *token)
{
	if (input[*idx] == '&' && input[*idx + 1] == '&')
	{
		*idx += 2;
		token->len = 2;
		token->types = AND;
		return (true);
	}
	if (input[*idx] == '|' && input[*idx + 1] == '|')
	{
		*idx += 2;
		token->len = 2;
		token->types = OR;
		return (true);
	}
	if (input[*idx] == '|')
	{
		*idx += 1;
		token->len = 1;
		token->types = PIPE;
		return (true);
	}
	return (false);
}

bool	is_parenthesis(const char *input, int *idx, t_token *token)
{
	if (input[*idx] == '(')
	{
		*idx += 1;
		token->len = 1;
		token->types = O_PARENTHESIS;
		return (true);
	}
	if (input[*idx] == ')')
	{
		*idx += 1;
		token->len = 1;
		token->types = C_PARENTHESIS;
		return (true);
	}
	return (false);
}

bool	is_redirection(const char *input, int *idx, t_token *token)
{
	if ((input[*idx] == '<' && input[*idx + 1] == '<') || \
		(input[*idx] == '>' && input[*idx + 1] == '>'))
	{
		if (input[*idx] == '<')
			token->types = REDIR | REDIR_HEREDOC;
		else
			token->types = REDIR | REDIR_OUT_APP;
		*idx += 2;
		token->len = 2;
		return (true);
	}
	else if (input[*idx] == '<' || input[*idx] == '>')
	{
		if (input[*idx] == '<')
			token->types = REDIR | REDIR_IN;
		else
			token->types = REDIR | REDIR_OUT;
		*idx += 1;
		token->len = 1;
		return (true);
	}
	return (false);
}

bool	is_text(const char *input, int *idx, t_token *token)
{
	int	len;

	len = 0;
	while (input[*idx + len] && ft_isspace(input[*idx + len]) == false && \
			ft_strchr("<>()|\'\"", input[*idx + len]) == NULL && \
			ft_strncmp("&&", input + *idx + len, 1) != 0)
		++len;
	if (len == 0)
		return (false);
	*idx += len;
	token->len = len;
	token->types = TEXT;
	if (input[*idx] == '\'' || input[*idx] == '\"')
		token->types |= CONNECTED;
	return (true);
}

bool	is_quote(const char *input, int *idx, t_token *token)
{
	int	len;

	if (input[*idx] == '\'' || input[*idx] == '\"')
	{
		len = 1;
		while (input[*idx + len] != '\0' && input[*idx] != input[*idx + len])
			++len;
		if (input[*idx + len] == '\0')
			return (print_error(ERR_SYNTAX, NULL, token->str));
		++token->str;
		++len;
		token->len = len - 2;
		if (input[*idx] == '\'')
			token->types = TEXT | SINGLE_QUOTE;
		else
			token->types = TEXT | DOUBLE_QUOTE;
		*idx += len;
		if (input[*idx] == '\'' || input[*idx] == '\"')
			token->types |= CONNECTED;
		return (true);
	}
	return (false);
}
