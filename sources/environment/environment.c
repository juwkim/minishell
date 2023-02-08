/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:08:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/09 03:27:37 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment/environment.h"

bool	env_init(void)
{
	extern char	**environ;
	char		*key;
	char		*value;
	int			idx;

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
		env_set(key, value);
		++environ;
	}
	return (true);
}

void	env_destroy(void)
{
	int	idx;

	idx = 0;
	while (idx < g_env.count)
	{
		free(g_env.key[idx]);
		free(g_env.value[idx]);
		++idx;
	}
}

void	env_set(char *key, char *value)
{
	int			idx;
	const int	len = ft_strlen(key);

	if (g_env.count == MAX_TABLE_SIZE)
		return ;
	idx = 0;
	while (idx < g_env.count && ft_strncmp(key, g_env.key[idx], len) != 0)
		++idx;
	if (idx != g_env.count)
	{
		free(g_env.key[g_env.count]);
		free(g_env.value[g_env.count]);
	}
	g_env.key[g_env.count] = key;
	g_env.value[g_env.count] = value;
	++g_env.count;
}

char	*env_get(char *key)
{
	int			idx;
	const int	len = ft_strlen(key);

	idx = 0;
	while (idx < g_env.count && ft_strncmp(key, g_env.key[idx], len) != 0)
		++idx;
	if (idx == g_env.count)
		return (NULL);
	else
		return (g_env.value[idx]);
}

void	env_remove(char *key)
{
	int			idx;
	const int	len = ft_strlen(key);

	idx = 0;
	while (idx < g_env.count && ft_strncmp(key, g_env.key[idx], len) != 0)
		++idx;
	if (idx == g_env.count)
		return ;
	free(g_env.key[idx]);
	free(g_env.value[idx]);
	--g_env.count;
	while (idx < g_env.count)
	{
		g_env.key[idx] = g_env.key[idx + 1];
		g_env.value[idx] = g_env.value[idx + 1];
		++idx;
	}
}
