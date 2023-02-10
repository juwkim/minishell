/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:08:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/10 16:51:40 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment/environment.h"

bool	env_init(void)
{
	extern char	**environ;
	char		*line;

	while (*environ)
	{
		line = ft_strdup(*environ);
		if (line == NULL)
		{
			env_destroy();
			return (print_error(NULL, NULL, strerror(errno)));
		}
		g_env.item[g_env.count++] = line;
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
		free(g_env.item[idx]);
		++idx;
	}
}

bool	env_set(const char *key, const char *val)
{
	char		*line;
	int			idx;
	const int	key_len = ft_strlen(key);

	if (g_env.count == MAX_TABLE_SIZE)
		return (print_error(NULL, NULL, "Environment variable table is full"));
	line = ft_strcjoin(key, val, '=');
	if (line == NULL)
		return (print_error(NULL, NULL, strerror(errno)));
	idx = 0;
	while (idx < g_env.count && \
				ft_strncmp(key, g_env.item[idx], key_len - 1) != 0)
		++idx;
	free(g_env.item[idx]);
	g_env.item[idx] = line;
	g_env.count += (idx == g_env.count);
	return (true);
}

char	*env_get(const char *key)
{
	int			idx;
	const int	key_len = ft_strlen(key);

	idx = 0;
	while (idx < g_env.count && \
			ft_strncmp(key, g_env.item[idx], key_len - 1) != 0)
		++idx;
	if (idx == g_env.count)
		return (NULL);
	else
		return (g_env.item[idx] + key_len + 1);
}

void	env_remove(const char *key)
{
	int			idx;
	const int	key_len = ft_strlen(key);

	idx = 0;
	while (idx < g_env.count && \
				ft_strncmp(key, g_env.item[idx], key_len - 1) != 0)
		++idx;
	if (idx == g_env.count)
		return ;
	free(g_env.item[idx]);
	--g_env.count;
	while (idx < g_env.count)
	{
		g_env.item[idx] = g_env.item[idx + 1];
		++idx;
	}
}
