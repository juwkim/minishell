/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:17:39 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 16:03:00 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander.h"

static int		set_cur_dir_files(t_list *list);
static t_list	*get_pattern_matched_files(t_list *cur_dir_files, \
													char *pattern);
static t_node	*list_merge(t_list *list1, t_node *prev, t_list *matched_files);

int	expand_wildcard(t_list *argv)
{
	t_list	cur_dir_files;
	t_list	*matched_files;
	t_node	*prev;
	t_node	*cur;

	if (set_cur_dir_files(&cur_dir_files) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	prev = argv->head->next;
	cur = argv->head->next->next;
	while (cur != NULL)
	{
		matched_files = get_pattern_matched_files(&cur_dir_files, cur->item);
		prev = list_merge(argv, prev, matched_files);
		cur = prev->next;
	}
	list_destroy(&cur_dir_files, free);
	return (EXIT_SUCCESS);
}

static int	set_cur_dir_files(t_list *list)
{
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir("./");
	if (dir == NULL)
		return (print_error("expander", "get_current_dir_files", NULL));
	list_init(list);
	dirent = readdir(dir);
	while (dirent != NULL)
	{
		if (list_push_back(list, ft_strdup(dirent->d_name)) == false)
		{
			list_destroy(list, free);
			return (print_error("expander", "get_current_dir_files", NULL));
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (EXIT_SUCCESS);
}

static t_list	*get_pattern_matched_files(t_list *cur_dir_files, char *pattern)
{
	t_list *const	matched_files = malloc(sizeof(t_list));
	t_node			*cur;
	const int		pattern_len = ft_strlen(pattern);

	if (matched_files == NULL || list_init(matched_files) == false)
		return (NULL);
	cur = cur_dir_files->head->next;
	while (cur != NULL)
	{
		if (is_pattern_match(cur->item, pattern, pattern_len) == true)
			list_push_back(matched_files, ft_strdup(cur->item));
		cur = cur->next;
	}
	if (list_is_empty(matched_files) == true)
		list_push_back(matched_files, ft_strdup(pattern));
	return (matched_files);
}

static t_node	*list_merge(t_list *list1, t_node *prev, t_list *matched_files)
{
	list_pop_next(prev, free);
	prev = list_insert_list(list1, prev, matched_files);
	free(matched_files->head);
	free(matched_files);
	return (prev);
}
