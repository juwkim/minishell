/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 07:27:48 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 07:31:10 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

// POSIX BASED EXIT STATUS
# define EXIT_MISUSE_SHELL_BUILTIN	2 // misuse of shell builtins
# define EXIT_NOEXEC				126 // command invoked cannot execute
# define EXIT_NOTFOUND				127 // command not found

int		exit_status_get(void);
void	exit_status_set(int status);

#endif // EXIT_STATUS_H
