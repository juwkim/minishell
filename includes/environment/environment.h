/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:07:57 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/09 04:43:55 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "global.h"

bool	env_init(void);
void	env_destroy(void);
void	env_set(const char *key, const char *val);
char	*env_get(const char *key);
void	env_remove(const char *key);

#endif // ENVIRONMENT_H
