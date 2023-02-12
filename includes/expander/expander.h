/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:19:48 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 16:03:29 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <dirent.h>
# include "global.h"
# include "utils/print.h"
# include "utils/exit_status.h"
# include "utils/environment.h"
# include "utils/signal_handler.h"

// env_variable.c
char	*expand_env_variable(const char *str, const int len);

// wildcard.c
int		expand_wildcard(t_list *argv);

// is_pattern_match.c
bool	is_pattern_match(char *str, char *pattern, int pattern_len);

#endif // EXPANDER_H
