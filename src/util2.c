/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:15:21 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/07/13 16:26:05 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		is_link(char *name)
{
	char		buf[1024];

	if (readlink(name, buf, 1024) != -1)
		return (1);
	return (0);
}

int		needs_dir_treatment(char *name, struct stat *s, int *status, int *is_ln)
{
	if ((*status = stat(name, s)) == 0
		&& !(does_cycle(name))
		&& !(*is_ln = is_link(name))
		&& (g_flags & F_DFILE) != F_DFILE
		&& S_ISDIR(s->st_mode))
		return (1);
	return (0);
}

int		needs_file_treatment(char *name, struct stat *s,
							const int *status, const int *is_ln)
{
	if(*status == 0 && (!S_ISDIR(s->st_mode) || does_cycle(name) || *is_ln
						|| g_flags & F_DFILE ))
		return (1);
	return (0);
}

size_t	malloc_str(va_list *args, size_t delimiter_size, char **whereto)
{
	char		*str;
	size_t		whole_size;
	size_t		i;

	i = 0;
	whole_size = 0;
	while ((str = va_arg(*args, char *)))
	{
		whole_size += ft_strlen(str);
		i++;
	}
	whole_size += delimiter_size * (i - 1);
	*whereto = ft_strnew(whole_size + 1);
	va_end(*args);
	return (whole_size + 1);
}

char	*strings_join(char *delimiter, ...)
{
	va_list		args;
	va_list		copy;
	size_t		size;
	char		*joined;
	char		*str;

	va_start(args, delimiter);
	va_copy(copy, args);
	size = malloc_str(&copy, ft_strlen(delimiter), &joined);
	while ((str = va_arg(args, char *)))
	{
		if (ft_strlen(str) == 0)
			continue ;
		ft_strlcat(joined, str, size);
		if (ft_strlcat(joined, delimiter, size) > size)
			break ;
	}
	va_end(args);
	return (joined);
}
