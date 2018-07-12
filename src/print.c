#include "../include/ft_ls.h"

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
	if (g_flags & F_LONG)
	{
		ft_printf("%s %*u %-*s %-*s %*lld %s %s -> %s\n",
				mode, g_param.linkw, file->links,
				g_param.userw, getpwuid(file->uid)->pw_name,
				g_param.groupw, getgrgid(file->gid)->gr_name,
				g_param.bytew, file->size, date, file->filename,
				file->whereto);
	}
	else
		ft_printf("%s \n", file->filename);
}

void	print_file(t_file *file)
{
	char *date;
	char *mode;

	mode = get_readable_mode(file);
	date = ft_strsub(ctime(&(file->mtime.tv_sec)), 4, 12);
	if (g_flags & F_LONG)
	{
		if (S_ISLNK(file->mode) && file->whereto != NULL)
			print_link(file, mode, date);
		else if (S_ISCHR(file->mode) || S_ISBLK(file->mode))
			print_device(file, mode, date);
		else
			ft_printf("%s %*u %-*s %-*s %*lld %s %s\n",
					mode, g_param.linkw, file->links,
					g_param.userw, getpwuid(file->uid)->pw_name,
					g_param.groupw, getgrgid(file->gid)->gr_name,
					g_param.bytew, file->size, date, file->filename);
	}
	else
		ft_printf("%s \n", file->filename);
	free(date);
	free(mode);
}


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

void	print_in_columns(t_file *list)
{

}

void	print_in_columns_across(t_file *list)
{
	int		j;
	int		i;
	int		len;
	t_file	**array;

	i = 0;
	array = to_array(list, (len = get_list_length(list)));
	g_param.ttyperline = g_param.ttyw / g_param.ttycolumnw;
	while (i < (g_param.ttycolumnw / len + 1))
	{
		j = 0;
		while (j < g_param.ttyperline && (i * g_param.ttyperline + j) < len)
		{
			ft_printf("%-*s", g_param.ttycolumnw,
					array[i * g_param.ttyperline + j]->filename);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	free(array);
}

void	print_in_columns_along(t_file *list)
{
	int		j;
	int		i;
	int		len;
	t_file	**array;

	i = 0;
	array = to_array(list, (len = get_list_length(list)));
	g_param.ttyperline = g_param.ttyw / g_param.ttycolumnw;
	while (i < (g_param.ttycolumnw / len + 1))
	{
		j = 0;
		while (j < g_param.ttyperline && (i + j * (g_param.ttycolumnw / len + 1)) < len)
		{
			ft_printf("%-*s", g_param.ttycolumnw,
					  array[i + j * (g_param.ttycolumnw / len + 1)]->filename);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	free(array);
}

void	print_directory(t_file *list)
{
	t_file	*copy;
	size_t	total;

	if ((g_flags & F_RECUR) && list != NULL && !IS_CURR(list->path))
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
	else if ((g_flags & F_COLUMN) || (g_flags & F_LONG) == 0)
	{
		print_in_columns_along(list);
		return ;
	}
	copy = list;
	while (copy)
	{
		print_file(copy);
		copy = copy->next;
	}
}
