/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:25:43 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/30 03:53:57 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "global.h"
# include "lexer/lexer.h"

# define TOK_TEXT			1
# define TOK_BIN_OP			2
# define TOK_PIPE			4

# define TOK_S_QUOTE		8
# define TOK_D_QUOTE		16
# define TOK_CONNECTED		32

# define TOK_O_PARENTHESIS	64
# define TOK_C_PARENTHESIS	128

# define TOK_REDIR			256
# define TOK_REDIR_OUT		512
# define TOK_REDIR_OUT_APP	1024
# define TOK_REDIR_IN		2048
# define TOK_REDIR_HEREDOC	4096

# define TOK_WILDCARD		8192

typedef struct s_token
{
	char	*str;
	int		len;
	int		types;
}	t_token;

// tokenizer.c
bool	tokenize(t_deque *tokens, const char *input);
void	destroy_tokens(t_deque *tokens);
t_token	*get_token(t_deque *tokens, int cur);
void	print_tokens(t_deque *tokens);

// tokenizer_utils.c
bool	is_bin_operator_or_pipe(const char *input, int *idx, t_token *token);
bool	is_parenthesis(const char *input, int *idx, t_token *token);
bool	is_redirection(const char *input, int *idx, t_token *token);
bool	is_text(const char *input, int *idx, t_token *token);
bool	is_quote(const char *input, int *idx, t_token *token);

#endif // TOKENIZER_H
