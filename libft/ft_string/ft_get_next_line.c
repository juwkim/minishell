/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 00:47:12 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/18 03:54:42 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int	get_line(char *buf, char **rest, ssize_t read_size, char **rtn)
{
	int		idx;
	char	*temp;

	buf[read_size] = '\0';
	idx = ft_strchr(buf, '\n') - buf;
	if (idx != -1 && buf[idx + 1])
	{
		*rest = ft_substr(buf, idx + 1, read_size - idx - 1);
		buf[idx] = '\0';
	}
	if (*rtn)
	{
		temp = ft_strjoin(*rtn, buf);
		free(*rtn);
		*rtn = temp;
	}
	else
		*rtn = ft_strdup(buf);
	return (idx != -1);
}

int	check_rest(char **rest, char **rtn)
{
	int		idx;
	int		len;
	char	*temp;

	len = ft_strlen(*rest);
	idx = ft_strfind(*rest, '\n');
	if (-1 < idx && idx < len - 1)
	{
		*rtn = ft_substr(*rest, 0, idx);
		temp = ft_substr(*rest, idx + 1, len - idx - 1);
		free(*rest);
		*rest = temp;
		return (1);
	}
	*rtn = *rest;
	*rest = NULL;
	return (idx != -1);
}

char	*get_next_line(int fd)
{
	const int	buffer_size = 8192;
	static char	*rest;
	char		buf[8192 + 1];
	char		*rtn;
	ssize_t		read_size;

	rtn = NULL;
	if (fd < 0)
		return (NULL);
	if (rest && check_rest(&rest, &rtn))
		return (rtn);
	read_size = read(fd, buf, buffer_size);
	while (read_size > 0 && get_line(buf, &rest, read_size, &rtn) == 0)
		read_size = read(fd, buf, buffer_size);
	return (rtn);
}
