/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:07:57 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/09 03:28:55 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "global.h"

bool	env_init(void);
void	env_destroy(void);
void	env_set(char *key, char *value);
char	*env_get(char *key);
void	env_remove(char *key);

#endif // ENVIRONMENT_H
