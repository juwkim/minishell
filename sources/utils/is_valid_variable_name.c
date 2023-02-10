/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_variable_name.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 07:11:50 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/11 07:52:25 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/is_valid_variable_name.h"

bool	is_valid_variable_name(const char *name)
{
	if (*name == '\0' || (ft_isalpha(*name) == false && *name != '_'))
		return (false);
	while (ft_isalnum(*name) == true || *name == '_')
		++name;
	return (*name == '\0' || *name == '=');
}
