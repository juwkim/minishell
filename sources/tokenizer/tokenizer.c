/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:56:06 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 06:54:06 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer/tokenizer.h"

static t_token	*create_token(const char *input, int *idx);

bool	tokenize(t_list *tokens, const char *input)
{
	int		idx;
	t_token	*token;

	idx = 0;
	if (list_init(tokens) == false)
		return (print_error(NULL, NULL));
	while (input[idx] != '\0')
	{
		if (ft_isspace(input[idx]))
		{
			++idx;
			continue ;
		}
		token = create_token(input, &idx);
		if (list_push_back(tokens, token) == false)
		{
			free(token);
			list_destroy(tokens, free);
			return (print_error(NULL, NULL));
		}
	}
	return (true);
}

static t_token	*create_token(const char *input, int *idx)
{
	t_token *const	token = malloc(sizeof(t_token));

	if (token == NULL)
		return (NULL);
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
