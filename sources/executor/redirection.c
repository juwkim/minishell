/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 05:25:08 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/14 07:26:08 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

static int	redirect_in(t_command *command);
static int	redirect_out(t_command *command);

int	redirect(t_command *command)
{
	if (command->in && redirect_in(command) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (command->out && redirect_out(command) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	redirect_builtin(t_command *command, int *old_fd_in, int *old_fd_out)
{
	*old_fd_in = dup(STDIN_FILENO);
	*old_fd_out = dup(STDOUT_FILENO);
	if (command->in && redirect_in(command) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (command->out && redirect_out(command) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	redirect_undo(int old_fd_in, int old_fd_out)
{
	if (dup2(old_fd_in, STDIN_FILENO) == -1 || close(old_fd_in) == -1)
		print_error(NULL, NULL, NULL);
	if (dup2(old_fd_out, STDOUT_FILENO) == -1 || close(old_fd_out) == -1)
		print_error(NULL, NULL, NULL);
}

static int	redirect_in(t_command *command)
{
	int	fd;

	if (command->is_in_heredoc)
		command->in = parse_heredoc(command->in);
	fd = open(command->in, O_RDONLY, S_IRUSR);
	if (fd < 0)
		return (print_error(command->in, NULL, NULL));
	if (command->is_in_heredoc == true && unlink(command->in) == -1)
		return (print_error(NULL, NULL, NULL));
	if (dup2(fd, STDIN_FILENO) == -1 || close(fd) == -1)
		return (print_error(NULL, NULL, NULL));
	return (EXIT_SUCCESS);
}

static int	redirect_out(t_command *command)
{
	int	fd;

	if (command->is_out_append)
		fd = open(command->out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(command->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (print_error(command->in, NULL, NULL));
	if (dup2(fd, STDOUT_FILENO) == -1 || close(fd) == -1)
		return (print_error(NULL, NULL, NULL));
	return (EXIT_SUCCESS);
}
