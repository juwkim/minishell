/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 04:50:12 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/30 23:01:38 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strdup(const char *s)
{
	char			*buf;
	const size_t	len = ft_strlen(s);

	buf = (char *) malloc(sizeof(char) * (len + 1));
	if (buf == NULL)
		return (NULL);
	ft_strlcpy(buf, s, len + 1);
	return (buf);
}

char	*ft_strndup(const char *s, size_t n)
{
	char			*buf;

	buf = (char *) malloc(sizeof(char) * (n + 1));
	if (buf == NULL)
		return (NULL);
	ft_strlcpy(buf, s, n + 1);
	return (buf);
}
