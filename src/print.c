/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:14:55 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/07/13 18:29:25 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	print_file_long(t_file *file, char *mode, char *date)
{
	int		size_minor;

	size_minor = g_param.majorw != 0 && g_param.minorw != 0 ?
				g_param.majorw + g_param.minorw + 1 : g_param.bytew;
	ft_printf("%s %*u %-*s %-*s %*lld %s %s\n", mode, g_param.linkw,
			  file->links, g_param.userw, getpwuid(file->uid)->pw_name,
			  g_param.groupw, getgrgid(file->gid)->gr_name,
			  size_minor, file->size, date, file->filename);
}

void	print_device(t_file *file, char *mode, char *date)
{
	if (g_flags & F_LONG)
	{
		ft_printf("%s %*u %-*s %-*s %*d,%*d %s %s\n",
				mode, g_param.linkw, file->links,
				g_param.userw, getpwuid(file->uid)->pw_name,
				g_param.groupw, getgrgid(file->gid)->gr_name,
				g_param.majorw, major(file->dev),
				g_param.minorw, minor(file->dev), date, file->filename);
	}
	else
		ft_printf("%s \n", file->filename);
}

void	print_link(t_file *file, char *mode, char *date)
{
	int		size_minor;

	if (g_param.majorw != 0 && g_param.minorw != 0)
		size_minor = g_param.majorw + g_param.minorw + 1;
	else
		size_minor = g_param.bytew;
	if (g_flags & F_LONG)
	{
		ft_printf("%s %*u %-*s %-*s %*lld %s %s -> %s\n",
				mode, g_param.linkw, file->links,
				g_param.userw, getpwuid(file->uid)->pw_name,
				g_param.groupw, getgrgid(file->gid)->gr_name,
				size_minor, file->size, date, file->filename,
				file->whereto);
	}
	else
		ft_printf("%s \n", file->filename);
}

void	print_file(t_file *file)
{
	char	*date;
	char	*mode;

	mode = get_readable_mode(file);
	date = ft_strsub(ctime(&(file->mtime.tv_sec)), 4, 12);
	if (g_flags & F_LONG)
	{
		if (S_ISLNK(file->mode) && file->whereto != NULL)
			print_link(file, mode, date);
		else if (S_ISCHR(file->mode) || S_ISBLK(file->mode))
			print_device(file, mode, date);
		else
			print_file_long(file, mode, date);
	}
	else
		ft_printf("%s \n", file->filename);
	free(date);
	free(mode);
}

void	print_directory(t_file *list)
{
	t_file	*copy;
	size_t	total;

	if (list != NULL && ((g_flags & F_RECUR) || !IS_CURR(list->path)))
		ft_printf("\n%s:\n", list->path);
	if ((g_flags & F_LONG) && list != NULL)
	{
		total = 0;
		copy = list;
		while (copy)
		{
			total += copy->blocks;
			copy = copy->next;
		}
		ft_printf("total %zu\n", total);
	}
	else if (!(g_flags & F_ONEPER) &&
		((g_flags & F_COLUMN) || (g_flags & F_LONG) == 0))
		return (print_in_columns(list));
	copy = list;
	while (copy)
	{
		print_file(copy);
		copy = copy->next;
	}
}
