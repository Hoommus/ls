/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:14:49 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/07/13 11:56:48 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_file	**to_array(t_file *file, int len)
{
	int		j;
	t_file	*copy;
	t_file	**array;

	array = (t_file **)malloc(sizeof(t_file *) * len);
	copy = file;
	j = 0;
	while (copy && j < len)
	{
		array[j++] = copy;
		copy = copy->next;
	}
	return (array);
}

int		get_list_length(t_file *list)
{
	int		len;
	t_file	*copy;

	len = 0;
	copy = list;
	while (copy && ++len)
		copy = copy->next;
	return (len);
}

void	print_in_columns_across(t_file **array, int len)
{
	int		j;
	int		i;
	int		rows;

	i = 0;
	rows = len / g_param.ttyperline;
	rows = rows == 0 ? 1 : rows;
	if (g_param.ttyw % g_param.ttycolumnw > 0)
		rows += 1;
	while (i < rows)
	{
		j = 0;
		while (j < g_param.ttyperline && (i * g_param.ttyperline + j) < len)
		{
			ft_printf(j < g_param.ttyperline - 1 ? "%-*s" : "%*1s",
					g_param.ttycolumnw,
					array[i * g_param.ttyperline + j]->filename);
			j++;
		}
		if (i < rows)
			ft_printf("\n");
		i++;
	}
}

void	print_in_columns_along(t_file **array, int len)
{
	int		j;
	int		i;
	int		rows;

	i = 0;
	rows = len / g_param.ttyperline;
	rows = rows == 0 ? 1 : rows;
	if (g_param.ttyw % g_param.ttycolumnw > 0)
		rows += 1;
	while (i < rows)
	{
		j = 0;
		while (j < g_param.ttyperline && (i + j * rows) < len)
		{
			ft_printf(j < g_param.ttyperline - 1 ? "%-*s" : "%*1s",
					g_param.ttycolumnw, array[i + j * rows]->filename);
			j++;
		}
		if (i < rows)
			ft_printf("\n");
		i++;
	}
}

void	print_in_columns(t_file *list)
{
	int		len;
	t_file	**array;

	array = to_array(list,
					(len = get_list_length(list)));
	g_param.ttyperline = g_param.ttyw / g_param.ttycolumnw;
	if (g_flags & F_ACROSS)
		print_in_columns_across(array, len);
	else
		print_in_columns_along(array, len);
	free(array);
}
