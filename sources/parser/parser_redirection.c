/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:12:46 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/07 07:14:45 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

// static void	parse_heredoc(t_list *arguments, char *delimiter);

void	parse_redirection(t_command *command, t_node **cur)
{
	char	*str;
	int		redirection_type;

	redirection_type = ((t_token *)(*cur)->item)->types;
	*cur = (*cur)->next;
	str = get_connected_str(cur);
	if (redirection_type & (REDIR_IN | REDIR_HEREDOC))
	{
		free(command->in);
		command->in = str;
		command->is_in_heredoc = (redirection_type & REDIR_HEREDOC) != 0;
	}
	else
	{
		free(command->out);
		command->out = str;
		command->is_out_append = (redirection_type & REDIR_OUT_APP) != 0;
	}
}

// static void	parse_heredoc(t_list *arguments, char *delimiter)
// {
// 	const int	fd = dup(STDIN_FILENO);
// 	char		*str;
// 	t_list		dq;

// 	dq_init(&dq);
// 	signal(SIGINT, sigint_heredoc_handler);
// 	while (true)
// 	{
// 		str = readline("> ");
// 		if (str == NULL || !ft_strncmp(str, delimiter, ft_strlen(delimiter)))
// 			break ;
// 		dq_push_back(&dq, str);
// 		dq_push_back(&dq, ft_strdup("\n"));
// 	}
// 	list_push_back(arguments, dq_strjoin(&dq));
// 	free(delimiter);
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// 	signal(SIGINT, sigint_handler);
// }
