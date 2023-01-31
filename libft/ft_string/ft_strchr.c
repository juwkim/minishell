/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 04:49:42 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/09 12:09:56 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strchr(char *s, int c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return (s);
	return (NULL);
}
