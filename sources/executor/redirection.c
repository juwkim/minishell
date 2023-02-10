/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 05:25:08 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 06:54:04 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static bool	redirect_in(t_command *command);
static bool	redirect_out(t_command *command);

bool	redirect(t_command *command, int *oldfd_in, int *oldfd_out)
{
	*oldfd_in = dup(STDIN_FILENO);
	*oldfd_out = dup(STDOUT_FILENO);
	if (*oldfd_in == -1 || *oldfd_out == -1)
		return (print_error(NULL, NULL));
	if (command->in && redirect_in(command) == false)
		return (false);
	if (command->out && redirect_out(command) == false)
		return (false);
	return (true);
}

static bool	redirect_in(t_command *command)
{
	const int	fd = open(command->in, O_RDONLY, S_IRUSR);

	if (fd < 0)
		return (print_error(command->in, strerror(errno)));
	if (command->is_in_heredoc == true && unlink(command->in) == -1)
		return (print_error(NULL, NULL));
	if (dup2(fd, STDIN_FILENO) == -1 || close(fd) == -1)
		return (print_error(NULL, NULL));
	return (true);
}

static bool	redirect_out(t_command *command)
{
	int	fd;

	if (command->is_out_append)
		fd = open(command->out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(command->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (print_error(command->in, strerror(errno)));
	if (dup2(fd, STDOUT_FILENO) == -1 || close(fd) == -1)
		return (print_error(NULL, NULL));
	return (true);
}

bool	redirect_undo(int oldfd_in, int oldfd_out)
{
	return (dup2(oldfd_in, STDIN_FILENO) != -1 && \
			dup2(oldfd_out, STDOUT_FILENO) != -1);
}
