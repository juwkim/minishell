/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:56:15 by hepple            #+#    #+#             */
/*   Updated: 2023/01/28 16:40:15 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/error.h"

bool	print_error(char *s1, char *s2, char *message)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	if (s1 != NULL)
	{
		write(STDERR_FILENO, ": ", ft_strlen(": "));
		write(STDERR_FILENO, s1, ft_strlen(s1));
	}
	if (s2 != NULL)
	{
		write(STDERR_FILENO, ": ", ft_strlen(": "));
		write(STDERR_FILENO, s2, ft_strlen(s2));
	}
	if (message != NULL)
	{
		write(STDERR_FILENO, ": ", ft_strlen(": "));
		write(STDERR_FILENO, message, ft_strlen(message));
	}
	write(STDERR_FILENO, "\n", ft_strlen("\n"));
	return (false);
}
