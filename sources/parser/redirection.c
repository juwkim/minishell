/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:12:46 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 08:57:34 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

static char	*parse_heredoc(char *delimiter);
static bool	parse_heredoc_prepare(char **file_name, \
										int *stdin_fd, int *file_fd);

bool	parse_redirection(t_command *command, t_node **cur)
{
	char		*str;
	const int	redirection_type = ((t_token *)(*cur)->item)->types;

	*cur = (*cur)->next;
	str = get_connected_str(cur);
	if (str == NULL)
		return (false);
	if (redirection_type & REDIR_HEREDOC)
		unlink(command->in);
	if (redirection_type & (REDIR_IN | REDIR_HEREDOC))
	{
		free(command->in);
		if (redirection_type & REDIR_IN)
			command->in = str;
		else
			command->in = parse_heredoc(str);
		command->is_in_heredoc = (redirection_type & REDIR_HEREDOC) != 0;
	}
	else
	{
		free(command->out);
		command->out = str;
		command->is_out_append = (redirection_type & REDIR_OUT_APP) != 0;
	}
	return (true);
}

static char	*parse_heredoc(char *delimiter)
{
	int			stdin_fd;
	char		*file_name;
	int			file_fd;
	char		*str;
	const int	len = ft_strlen(delimiter);

	signal(SIGINT, sigint_heredoc_handler);
	if (parse_heredoc_prepare(&file_name, &stdin_fd, &file_fd) == false)
		return (NULL);
	str = readline("> ");
	while (str != NULL && ft_strncmp(str, delimiter, len) != 0)
	{
		write(file_fd, str, ft_strlen(str));
		write(file_fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	free(str);
	free(delimiter);
	close(file_fd);
	close(STDIN_FILENO);
	dup2(stdin_fd, STDIN_FILENO);
	signal(SIGINT, sigint_handler);
	return (file_name);
}

static bool	parse_heredoc_prepare(char **file_name, int *stdin_fd, int *file_fd)
{
	static int	num;
	char		*stred_num;
	bool		res;

	*stdin_fd = dup(STDIN_FILENO);
	res = true;
	*file_fd = -1;
	while (*file_fd == -1)
	{
		stred_num = ft_itoa(num++);
		*file_name = ft_strjoin("heredoc_temp_file_", stred_num);
		free(stred_num);
		if (*file_name == NULL)
		{
			res = false;
			print_error(NULL, NULL, NULL);
			break ;
		}
		*file_fd = open(*file_name, O_WRONLY | O_CREAT | O_EXCL, 0600);
	}
	return (res);
}
