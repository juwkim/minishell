/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:08:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/09 04:15:53 by juwkim           ###   ########.fr       */
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
			return (print_error(NULL, NULL, strerror(ENOMEM)));
		}
		env_set(line);
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

void	env_set(char *line)
{
	int			idx;
	const int	key_len = ft_strfind(line, '=');

	if (g_env.count == MAX_TABLE_SIZE)
	{
		free(line);
		return ;
	}
	idx = 0;
	while (idx < g_env.count && ft_strncmp(line, g_env.item[idx], key_len) != 0)
		++idx;
	if (idx != g_env.count)
		free(g_env.item[g_env.count]);
	g_env.item[g_env.count] = line;
	++g_env.count;
}

char	*env_get(char *key)
{
	int			idx;
	const int	key_len = ft_strlen(key);

	idx = 0;
	while (idx < g_env.count && ft_strncmp(key, g_env.item[idx], key_len) != 0)
		++idx;
	free(key);
	if (idx == g_env.count)
		return (NULL);
	else
		return (ft_strdup(g_env.item[idx] + key_len + 1));
}

void	env_remove(char *key)
{
	int			idx;
	const int	key_len = ft_strlen(key);

	idx = 0;
	while (idx < g_env.count && ft_strncmp(key, g_env.item[idx], key_len) != 0)
		++idx;
	free(key);
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
