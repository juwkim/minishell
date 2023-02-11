/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:05:24 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 07:31:44 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <limits.h>
# include "global.h"
# include "utils/exit_status.h"
# include "utils/environment.h"
# include "utils/is_valid_variable_name.h"

# define BUILTIN_FUNC_CNT 7

void	builtin_exit(char **argv, bool is_subshell);

void	builtin_echo(char **argv);

void	builtin_cd(char **argv);

void	builtin_pwd(char **argv);

void	builtin_env(char **argv);

void	builtin_export(char **argv);

void	builtin_unset(char **argv);

#endif // BUILTIN_H