/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:19:48 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/03 19:55:10 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "global.h"
# include "parser/parser.h"
# include "executor/executor.h"

bool	expand(t_deque *commands);
char	*expand_env_variable(char *str, int len);

#endif // EXPANDER_H
