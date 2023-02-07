/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:08:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/07 23:53:20 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment/environment.h"

bool	env_init(void)
{
	extern char	**environ;
	t_key		key;
	t_value		value;
	int			idx;

	hash_table_init(&g_env);
	while (*environ)
	{
		idx = ft_strfind(*environ, '=');
		key = ft_strndup(*environ, idx);
		value = ft_strdup(*environ + idx + 1);
		if (key == NULL || value == NULL)
		{
			free(key);
			free(value);
			env_destroy();
			return (print_error(NULL, NULL, strerror(ENOMEM)));
		}
		hash_table_insert(&g_env, key, value);
		++environ;
	}
	return (true);
}

void	env_destroy(void)
{
	hash_table_destroy(&g_env);
}
