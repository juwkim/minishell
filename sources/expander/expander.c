/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:19:27 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/04 03:24:17 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander.h"

static char	*get_env_variable(char *str, int *i, int len);

char	*expand_env_variable(char *str, int len)
{
	int		i;
	t_deque	dq;

	i = 0;
	dq_init(&dq);
	while (i < len)
	{
		while (str[i] == '$' && str[i + 1] == '$')
			++i;
		if (str[i] == '$' && str[i + 1] == '?')
		{
			dq_push_back(&dq, ft_itoa(exit_status_get()));
			++i;
		}
		else if (str[i] == '$' && i < len - 1)
		{
			++i;
			dq_push_back(&dq, get_env_variable(str, &i, len));
		}
		else
			dq_push_back(&dq, ft_strndup(str + i, 1));
		++i;
	}
	return (dq_strjoin(&dq));
}

static char	*get_env_variable(char *str, int *i, int len)
{
	const int	start = *i;
	char		*val;
	char		*key;

	while (*i < len && (ft_isalnum(str[*i]) || str[*i] == '_'))
		++(*i);
	key = ft_strndup(str + start, *i - start);
	val = hash_table_search(&g_env, key);
	free(key);
	--(*i);
	return (ft_strdup(val));
}

// static char	*expand_wildcard(char *str)
// {
// 	return (str);
// }
