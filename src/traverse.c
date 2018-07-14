/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:15:10 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/07/14 14:53:03 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

/*
** Function creates list with files in _dirname_ directory.
** It does not add hidden files unless F_ALL (-a) flag specified.
*/

t_file	*get_directory_contents(char *dirname, DIR *dir)
{
	char			*full_path;
	t_file			*list_head;
	t_file			*list_tail;
	struct stat		st;
	struct dirent	*ent;

	list_head = NULL;
	list_tail = NULL;
	while ((ent = readdir(dir)) != NULL)
	{
		if (stat(full_path = create_path(dirname, ent->d_name), &st) == 0)
		{
			if ((ent->d_type & DT_LNK) == DT_LNK)
				lstat(full_path, &st);
			if (!(ent->d_name[0] == '.' && (g_flags & F_ALL) != 2))
			{
				list_add(&list_head, &list_tail,
						set_widths(create_file(&st, ent->d_name, dirname)));
			}
		}
		else
			ft_printf("ft_ls: %s: %s\n", dirname, strerror(errno));
		free(full_path);
	}
	return (list_head);
}
