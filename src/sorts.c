/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:15:05 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/07/14 16:28:44 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_sort_func		get_sort(void)
{
	if (g_flags & F_SORTT)
		return (&compare_by_mtime);
	else if (g_flags & F_SORTS)
		return (&compare_by_size);
	else if (g_flags & F_SORTA)
		return (&compare_by_atime);
	else if (g_flags & F_SORTC)
		return (&compare_by_ctime);
	else if (g_flags & F_NSORT)
		return (NULL);
	else
		return (&compare_by_filename);
}

t_file			*sort(t_file *list, int (*compare)(t_file *, t_file *))
{
	t_file	*head;

	if (compare == NULL || get_list_length(list) > 2000)
		return (list);
	head = list;
	while (list != NULL && list->next != NULL)
	{
		if (compare(list, list->next) > 0)
		{
			list_swap(head, list, list->next);
			list = head;
			continue ;
		}
		list = list->next;
	}
	return (head);
}

int				compare_by_filename(t_file *a, t_file *b)
{
	return ((g_flags & F_SORTR ? -1 : 1) * ft_strcmp(a->filename, b->filename));
}

int				compare_by_size(t_file *a, t_file *b)
{
	return ((g_flags & F_SORTR ? -1 : 1) * ((a->size - b->size) > 0));
}
