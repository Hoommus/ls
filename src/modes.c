/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:15:27 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/07/13 11:15:27 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char	get_file_type(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISSOCK(mode))
		return ('s');
	else
		return ('-');
}

char	get_sticky_bit(t_file *file)
{
	char		buffer[1024];
	acl_t		acl;
	acl_entry_t	e;

	acl = acl_get_link_np(file->full_name, ACL_TYPE_EXTENDED);
	if (listxattr(file->full_name, buffer, 1024, XATTR_NOFOLLOW) > 0)
	{
		if (acl != NULL)
			acl_free(acl);
		return ('@');
	}
	else if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &e) > -1)
	{
		acl_free(acl);
		return ('+');
	}
	return (' ');
}

char	*get_readable_mode(t_file *file)
{
	char	*m;
	mode_t	mode;

	mode = file->mode;
	m = ft_strnew(11);
	m[0] = get_file_type(mode);
	m[1] = (char)((mode & S_IRUSR) ? 'r' : '-');
	m[2] = (char)((mode & S_IWUSR) ? 'w' : '-');
	m[3] = (char)((mode & S_IXUSR) ? 'x' : '-');
	m[4] = (char)((mode & S_IRGRP) ? 'r' : '-');
	m[5] = (char)((mode & S_IWGRP) ? 'w' : '-');
	m[6] = (char)((mode & S_IXGRP) ? 'x' : '-');
	m[7] = (char)((mode & S_IROTH) ? 'r' : '-');
	m[8] = (char)((mode & S_IWOTH) ? 'w' : '-');
	m[9] = (char)((mode & S_IXOTH) ? 'x' : '-');
	m[10] = get_sticky_bit(file);
	return (m);
}
