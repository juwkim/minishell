/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:05:24 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/09 00:13:06 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "global.h"

# define BUILTIN_FUNC_CNT 7

int	builtin_exit(t_list *argv, bool is_subshell);

int	builtin_echo(t_list *argv);

int	builtin_cd(t_list *argv);

int	builtin_pwd(t_list *argv);

int	builtin_env(t_list *argv);

int	builtin_export(t_list *argv);

int	builtin_unset(t_list *argv);

#endif // BUILTIN_H