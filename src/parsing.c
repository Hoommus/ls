/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:15:07 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/07/13 11:15:07 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		get_another_flag(char f)
{
	if (f == 'f')
		return (F_NSORT);
	else if (f == 'S')
		return (F_SORTS);
	else if (f == 'u')
		return (F_SORTA);
	else if (f == 'U')
		return (F_SORTC);
	else if (f == 'C')
		return (F_COLUMN);
	else if (f == '1')
		return (F_ONEPER);
	else if (f == 'x')
		return (F_ACROSS);
	else
		return (throw_illegal_option(f));
}

int		get_flag(char f)
{
	if (f == 'l')
		return (F_LONG);
	else if (f == 'a')
		return (F_ALL);
	else if (f == 't')
		return (F_SORTT);
	else if (f == 'r')
		return (F_SORTR);
	else if (f == 'R')
		return (F_RECUR);
	else if (f == 'G')
		return (F_COLOR);
	else if (f == 'd')
		return (F_DFILE);
	else
		return (get_another_flag(f));
}

int		parse_flags(int count, char **str)
{
	int		i;
	char	*copy;

	i = 0;
	while (i < count)
	{
		if (str[i][0] != '-' || str[i][1] == '\0')
			break ;
		copy = str[i] + 1;
		while (*copy)
			g_flags |= get_flag(*copy++);
		i++;
	}
	return (i);
}
