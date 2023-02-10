/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:05:24 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 06:58:27 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <limits.h>
# include "global.h"
# include "executor/executor.h"

# define BUILTIN_FUNC_CNT 7

int	builtin_exit(char **argv, bool is_subshell);

int	builtin_echo(char **argv);

int	builtin_cd(char **argv);

int	builtin_pwd(char **argv);

int	builtin_env(char **argv);

int	builtin_export(char **argv);

int	builtin_unset(char **argv);

#endif // BUILTIN_H