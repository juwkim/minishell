/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:08:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/28 23:43:28 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment/environment.h"

bool	env_init(void)
{
	extern char	**environ;
	char		*tmp;

	dq_init(&g_env);
	while (*environ)
	{
		tmp = ft_strdup(*environ);
		if (tmp == NULL)
		{
			env_destroy();
			return (print_error(NULL, NULL, strerror(ENOMEM)));
		}
		dq_push_back(&g_env, tmp);
		++environ;
	}
	return (true);
}

void	env_destroy(void)
{
	int	cur;

	cur = g_env.head;
	while (cur != g_env.tail)
	{
		free(g_env.items[cur]);
		cur = (cur + 1) % QUEUE_SIZE;
	}
}

// char	*env_get_value(char *name)
// {
// 	char	*env_var;

// 	env_var = env_find_var(name);
// 	if (env_var)
// 		return (ft_strchr(env_var, '=') + 1);
// 	else
// 		return (NULL);
// }

// char	*env_find_var(char *name)
// {
// 	char	*tmp;
// 	int		l_name;
// 	int		i;

// 	tmp = ft_strchr(name, '=');
// 	if (tmp == NULL)
// 		l_name = ft_strlen(name);
// 	else
// 		l_name = ft_strchr(name, '=') - name;
// 	i = 0;
// 	while (g_env[i])
// 	{
// 		if (!ft_strncmp(name, g_env[i], l_name) && g_env[i][l_name] == '=')
// 			return (g_env[i]);
// 		++i;
// 	}
// 	return (NULL);
// }

// bool	env_var_is_value(char *var_name, char *value)
// {
// 	const char	*env_value = env_get_value(var_name);

// 	return (env_value && ft_strncmp(env_value, value, ft_strlen(value)) == 0);
// }

// bool	env_is_var_char(char c)
// {
// 	return (ft_isalnum(c) || c == '_');
// }
