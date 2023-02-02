/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 06:23:04 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/03 07:43:29 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

void	hash_table_init(t_hash_table *table)
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
		table->items[i++].key = NULL;
}

void	hash_table_destroy(t_hash_table *table)
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		free(table->items[i++].key);
		free(table->items[i++].value);
	}
}

void	hash_table_insert(t_hash_table *table, t_key key, t_value value)
{
	const uint32_t	hash = murmurhash3_x86_32(key, ft_strlen(key), INT32_MAX);
	uint32_t		start;
	uint32_t		cur;

	start = hash % TABLE_SIZE;
	cur = start;
	while (table->items[cur].key != NULL && \
			ft_strncmp(table->items[cur].key, key, ft_strlen(key)) != 0)
	{
		cur = (cur + 1) % TABLE_SIZE;
		if (cur == start)
		{
			printf("Hash table is full\n");
			return ;
		}
	}
	if (table->items[cur].key == NULL)
	{
		table->items[cur].key = key;
		table->items[cur].value = value;
	}
}

void	hash_table_remove(t_hash_table *table, t_key key)
{
	const uint32_t	hash = murmurhash3_x86_32(key, ft_strlen(key), INT32_MAX);
	uint32_t		start;
	uint32_t		cur;
	bool			is_find;

	start = hash % TABLE_SIZE;
	cur = start;
	is_find = true;
	while (ft_strncmp(table->items[cur].key, key, ft_strlen(key)) != 0)
	{
		cur = (cur + 1) % TABLE_SIZE;
		if (cur == start)
		{
			is_find = false;
			break ;
		}
	}
	if (is_find)
	{
		free(table->items[cur].key);
		free(table->items[cur].value);
		table->items[cur].key = NULL;
	}
}

t_value	hash_table_search(t_hash_table *table, t_key key)
{
	const uint32_t	hash = murmurhash3_x86_32(key, ft_strlen(key), INT32_MAX);
	uint32_t		start;
	uint32_t		cur;
	bool			is_find;

	start = hash % TABLE_SIZE;
	cur = start;
	is_find = true;
	while (ft_strncmp(table->items[cur].key, key, ft_strlen(key)) != 0)
	{
		cur = (cur + 1) % TABLE_SIZE;
		if (cur == start)
		{
			is_find = false;
			break ;
		}
	}
	if (is_find)
		return (table->items[cur].value);
	else
		return (NULL);
}
