/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:19:27 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/10 10:57:45 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander.h"

static char	*get_env_variable(const char *str, int *i, const int len);

char	*expand_env_variable(const char *str, const int len)
{
	t_list	list;
	int		i;
	int		ret;

	if (list_init(&list) == false)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		while (str[i] == '$' && str[i + 1] == '$')
			++i;
		if (str[i] == '$' && str[i + 1] == '?')
		{
			++i;
			ret = list_push_back(&list, ft_itoa(exit_status_get()));
		}
		else if (str[i] == '$' && i < len - 1)
			ret = list_push_back(&list, get_env_variable(str, &i, len));
		else
			ret = list_push_back(&list, ft_strndup(str + i, 1));
		if (ret == false)
			return (NULL);
	}
	return (list_strjoin(&list));
}

static char	*get_env_variable(const char *str, int *i, const int len)
{
	int		start;
	char	*val;
	char	*key;

	(*i)++;
	start = *i;
	while (*i < len && (ft_isalnum(str[*i]) || str[*i] == '_'))
		++(*i);
	key = ft_strndup(str + start, *i - start);
	if (key == NULL)
		return (NULL);
	val = env_get(key);
	free(key);
	--(*i);
	return (ft_strdup(val));
}
