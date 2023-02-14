/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 03:25:15 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/14 10:27:09 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer/tokenizer.h"

int	is_bin_operator_or_pipe(const char *input, int *idx, t_token *token)
{
	if (input[*idx] == '&' && input[*idx + 1] == '&')
	{
		*idx += 2;
		token->len = 2;
		token->types = AND;
		return (EXIT_SUCCESS);
	}
	if (input[*idx] == '|' && input[*idx + 1] == '|')
	{
		*idx += 2;
		token->len = 2;
		token->types = OR;
		return (EXIT_SUCCESS);
	}
	if (input[*idx] == '|')
	{
		*idx += 1;
		token->len = 1;
		token->types = PIPE;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	is_parenthesis(const char *input, int *idx, t_token *token)
{
	if (input[*idx] == '(')
	{
		*idx += 1;
		token->len = 1;
		token->types = O_PARENTHESIS;
		return (EXIT_SUCCESS);
	}
	if (input[*idx] == ')')
	{
		*idx += 1;
		token->len = 1;
		token->types = C_PARENTHESIS;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	is_redirection(const char *input, int *idx, t_token *token)
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
		return (EXIT_SUCCESS);
	}
	else if (input[*idx] == '<' || input[*idx] == '>')
	{
		if (input[*idx] == '<')
			token->types = REDIR | REDIR_IN;
		else
			token->types = REDIR | REDIR_OUT;
		*idx += 1;
		token->len = 1;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	is_text(const char *input, int *idx, t_token *token)
{
	int	len;

	len = 0;
	while (input[*idx + len] && ft_isspace(input[*idx + len]) == false && \
			ft_strchr("<>()|\'\"", input[*idx + len]) == NULL && \
			ft_strncmp("&&", input + *idx + len, 2) != 0)
		++len;
	if (len == 0)
		return (EXIT_FAILURE);
	*idx += len;
	token->len = len;
	token->types = TEXT;
	if (input[*idx] == '\'' || input[*idx] == '\"')
		token->types |= CONNECTED;
	return (EXIT_SUCCESS);
}

int	is_quote(const char *input, int *idx, t_token *token)
{
	int	len;

	if (input[*idx] != '\'' && input[*idx] != '\"')
		return (EXIT_FAILURE);
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
	if (ft_strchr("<>()|&", input[*idx]) == NULL && \
		ft_isspace(input[*idx]) == false)
		token->types |= CONNECTED;
	return (EXIT_SUCCESS);
}
