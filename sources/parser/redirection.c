/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:12:46 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/14 07:26:21 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

static int	parse_heredoc_prepare(char **file_name, int *file_fd);
static void	read_heredoc(int file_fd, char *delimiter);

int	parse_redirection(t_command *command, t_node **cur)
{
	char		*str;
	const int	redirection_type = ((t_token *)(*cur)->item)->types;

	*cur = (*cur)->next;
	str = get_connected_str(cur);
	if (str == NULL)
		return (EXIT_FAILURE);
	if (redirection_type & REDIR_HEREDOC)
		unlink(command->in);
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
	return (EXIT_SUCCESS);
}

char	*parse_heredoc(char *delimiter)
{
	int			file_fd;
	char		*file_name;
	int			pid;

	parse_heredoc_prepare(&file_name, &file_fd);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		signal(SIGINT, sigint_heredoc_handler);
		read_heredoc(file_fd, delimiter);
		exit(EXIT_SUCCESS);
	}
	free(delimiter);
	close(file_fd);
	exit_status_set(execute_wait_pid(pid));
	return (file_name);
}

static int	parse_heredoc_prepare(char **file_name, int *file_fd)
{
	static int	num;
	char		*stred_num;
	int			res;

	res = EXIT_SUCCESS;
	*file_fd = -1;
	while (*file_fd == -1)
	{
		stred_num = ft_itoa(num++);
		*file_name = ft_strjoin("heredoc_temp_file_", stred_num);
		free(stred_num);
		if (*file_name == NULL)
		{
			res = EXIT_FAILURE;
			print_error(NULL, NULL, NULL);
			break ;
		}
		*file_fd = open(*file_name, O_WRONLY | O_CREAT | O_EXCL, 0600);
	}
	return (res);
}

static void	read_heredoc(int file_fd, char *delimiter)
{
	char		*str;
	char		*expanded;

	str = readline("> ");
	while (str != NULL && ft_strcmp(str, delimiter) != 0)
	{
		expanded = expand_env_variable(str, ft_strlen(str));
		write(file_fd, expanded, ft_strlen(expanded));
		write(file_fd, "\n", 1);
		free(str);
		free(expanded);
		str = readline("> ");
	}
}
