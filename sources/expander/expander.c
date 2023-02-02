/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:19:27 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/03 07:45:13 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander.h"

// bool	expand(t_deque *commands)
// {
// 	return (true);
// }


char	*expand_double_quote(char *str, int len)
{
	printf("haha: %s", hash_table_search(&g_env, "test"));
	return (ft_strndup(str, len));
}

// static char	*expand_wildcard(char *str)
// {
// 	return (str);
// }
