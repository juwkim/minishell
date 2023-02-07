/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:56:06 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/07 23:46:53 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer/tokenizer.h"

static t_token	*create_token(const char *input, int *idx);

bool	tokenize(t_list *tokens, const char *input)
{
	int		idx;
	t_token	*token;

	idx = 0;
	list_init(tokens);
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
			list_destroy(tokens, free);
			return (false);
		}
		list_push_back(tokens, token);
	}
	return (true);
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

void	print_tokens(const t_list *tokens)
{
	t_node		*cur;
	t_token		*token;

	cur = tokens->head->next;
	write(STDIN_FILENO, RED"Token:\t\t\t"DEF_COLOR, 23);
	while (cur->next != NULL)
	{
		token = cur->item;
		write(STDIN_FILENO, token->str, token->len);
		if (token->types & CONNECTED)
			write(STDIN_FILENO, GREEN" + "DEF_COLOR, 17);
		else
			write(STDIN_FILENO, GREEN" : "DEF_COLOR, 17);
		cur = cur->next;
	}
	token = cur->item;
	write(STDIN_FILENO, token->str, token->len);
	write(STDIN_FILENO, "\n", 1);
}
