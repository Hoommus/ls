/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:15:18 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/07/13 14:49:03 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char	*create_path(char *oldpath, char *filename)
{
	char	*full;

	oldpath = ft_strjoin(oldpath, "/");
	full = ft_strjoin(oldpath, filename);
	free(oldpath);
	return (full);
}

void	set_dev_width(t_file *single)
{
	int		nbrlen;

	if (single->dev)
	{
		nbrlen = ft_nbrlen(major(single->dev));
		if (g_param.majorw < nbrlen)
			g_param.majorw = nbrlen;
		nbrlen = ft_nbrlen(minor(single->dev));
		if (g_param.minorw < nbrlen)
			g_param.minorw = nbrlen;
	}
}

t_file	*set_widths(t_file *single)
{
	int		nbrlen;
	char	*user;
	char	*group;

	user = getpwuid(single->uid)->pw_name;
	group = getgrgid(single->gid)->gr_name;
	if (g_param.bytew < (nbrlen = ft_nbrlen(single->size)))
		g_param.bytew = nbrlen;
	if (g_param.linkw < (nbrlen = ft_nbrlen(single->links)))
		g_param.linkw = nbrlen;
	if (g_param.groupw < (nbrlen = ft_strlen(group)))
		g_param.groupw = nbrlen + 1;
	if (g_param.userw < (nbrlen = ft_strlen(user)))
		g_param.userw = nbrlen + 1;
	if (g_param.ttycolumnw < (nbrlen = ft_strlen(single->filename)))
		g_param.ttycolumnw = nbrlen + 2;
	set_dev_width(single);
	return (single);
}

void	clear_widths(void)
{
	g_param.ttycolumnw = 0;
	g_param.groupw = 0;
	g_param.bytew = 0;
	g_param.linkw = 0;
	g_param.userw = 0;
}

/*
** Yet another crutch, u know
*/

int		does_cycle(char *pth)
{
	size_t	i;

	i = ft_strlen(pth);
	if (i < 3 || !(g_flags & F_RECUR))
		return (0);
	if (i > 3 && ((pth[i - 2] == '/' && pth[i - 1] == '.' && pth[i] == '\0')
		|| (pth[i - 3] == '/' && pth[i - 2] == '.' && pth[i - 1] == '.')
		|| (pth[i - 2] == '/' && pth[i - 1] == '.' && !ft_isalnum(pth[i]))))
	{
		return (1);
	}
	return (0);
}
