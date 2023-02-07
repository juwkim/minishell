/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:19:27 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/07 23:51:48 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander.h"

static char	*get_env_variable(const char *str, int *i, const int len);

char	*expand_env_variable(const char *str, const int len)
{
	int		i;
	t_list	list;

	i = 0;
	list_init(&list);
	while (i < len)
	{
		while (str[i] == '$' && str[i + 1] == '$')
			++i;
		if (str[i] == '$' && str[i + 1] == '?')
		{
			list_push_back(&list, ft_itoa(exit_status_get()));
			++i;
		}
		else if (str[i] == '$' && i < len - 1)
		{
			++i;
			list_push_back(&list, get_env_variable(str, &i, len));
		}
		else
			list_push_back(&list, ft_strndup(str + i, 1));
		++i;
	}
	return (list_strjoin(&list));
}

static char	*get_env_variable(const char *str, int *i, const int len)
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
