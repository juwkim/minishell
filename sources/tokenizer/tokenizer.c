/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:56:06 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/30 16:55:48 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer/tokenizer.h"

static t_token	*create_token(const char *input, int *idx);

bool	tokenize(t_deque *tokens, const char *input)
{
	int		idx;
	t_token	*token;

	idx = 0;
	dq_init(tokens);
	while (input[idx] != '\0')
	{
		if (ft_isspace(input[idx]))
		{
			++idx;
			continue ;
		}
		token = create_token(input, &idx);
		if (token == NULL)
		{
			destroy_tokens(tokens);
			return (false);
		}
		dq_push_back(tokens, token);
	}
	return (true);
}

void	destroy_tokens(t_deque *tokens)
{
	int		cur;

	cur = tokens->head;
	while (cur != tokens->tail)
	{
		free(tokens->items[cur]);
		cur = (cur + 1) % QUEUE_SIZE;
	}
}

static t_token	*create_token(const char *input, int *idx)
{
	t_token *const	token = malloc(sizeof(t_token));

	if (token == NULL)
	{
		print_error(NULL, NULL, strerror(ENOMEM));
		return (NULL);
	}
	token->str = (char *) input + *idx;
	if (is_bin_operator_or_pipe(input, idx, token) == true)
		return (token);
	if (is_parenthesis(input, idx, token) == true)
		return (token);
	if (is_redirection(input, idx, token) == true)
		return (token);
	if (is_text(input, idx, token) == true)
		return (token);
	if (is_quote(input, idx, token) == true)
		return (token);
	free(token);
	return (NULL);
}

t_token	*get_token(t_deque *tokens, int cur)
{
	return ((t_token *) tokens->items[cur]);
}

void	print_tokens(t_deque *tokens)
{
	int			cur;
	int			flag;
	t_token		*token;
	const char	*text[15] = {"TEXT", "BIN_OP", "PIPE", "S_QUOTE", "D_QUOTE", \
	"CONNECTED", "O_PARENTHESIS", "C_PARENTHESIS", "REDIR", "REDIR_OUT", \
	"REDIR_OUT_APP", "REDIR_IN", "REDIR_HEREDOC", "WILDCARD"};

	cur = tokens->head;
	flag = 0;
	while (cur != tokens->tail)
	{
		token = tokens->items[cur];
		write(1, token->str, token->len);
		while (flag <= 14)
		{
			if (token->types & (1 << flag))
				printf(" %s", text[flag]);
			++flag;
		}
		printf("\n");
		flag = 0;
		cur = (cur + 1) % QUEUE_SIZE;
	}
}
