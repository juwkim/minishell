/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:12:46 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/31 21:49:13 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

static void	parse_heredoc(t_linked_list *arguments, char *delimiter);

void	parse_redirection(t_command *command, t_deque *tokens, int *cur)
{
	char	*str;
	int		redirection_type;
	t_token	*token;

	str = NULL;
	redirection_type = get_token(tokens, (*cur)++)->types;
	while (*cur != tokens->tail)
	{
		token = get_token(tokens, *cur);
		str = ft_strjoin(str, ft_strndup(token->str, token->len));
		if ((token->types & TOK_CONNECTED) == 0)
			break ;
		*cur = (*cur + 1) % QUEUE_SIZE;
	}
	if (redirection_type & TOK_REDIR_IN)
		command->in = str;
	else if (redirection_type & TOK_REDIR_OUT)
		command->out = str;
	else if (redirection_type & TOK_REDIR_OUT_APP)
		command->outapp = str;
	else
		parse_heredoc(&command->argv, str);
}

static void	parse_heredoc(t_linked_list *arguments, char *delimiter)
{
	const int	fd = dup(STDIN_FILENO);
	char		*str;
	char		*readed;

	readed = NULL;
	signal(SIGINT, sigint_heredoc_handler);
	remove_comma(delimiter);
	while (true)
	{
		str = readline("> ");
		if (str == NULL || !ft_strncmp(str, delimiter, ft_strlen(delimiter)))
			break ;
		readed = ft_strnewlinejoin(readed, str);
	}
	list_push_back(arguments, readed);
	free(str);
	free(delimiter);
	dup2(fd, STDIN_FILENO);
	close(fd);
	signal(SIGINT, sigint_handler);
}
