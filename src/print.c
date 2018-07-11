#include "../include/ft_ls.h"

void	print_device(t_file *file, char *mode, char *date)
{
	if (g_flags & F_LONG)
	{
		ft_printf("%s %*u %-*s %-*s %*d,%*d %s %s\n",
				mode, g_params.linkw, file->links,
				g_params.userw, getpwuid(file->uid)->pw_name,
				g_params.groupw, getgrgid(file->gid)->gr_name,
				g_params.majorw, major(file->dev),
				g_params.minorw, minor(file->dev), date, file->filename);
	}
	else
		ft_printf("%s \n", file->filename);
}

void	print_link(t_file *file, char *mode, char *date)
{
	if (g_flags & F_LONG)
	{
		ft_printf("%s %*u %-*s %-*s %*lld %s %s -> %s\n",
				mode, g_params.linkw, file->links,
				g_params.userw, getpwuid(file->uid)->pw_name,
				g_params.groupw, getgrgid(file->gid)->gr_name,
				g_params.bytew, file->size, date, file->filename,
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
					mode, g_params.linkw, file->links,
					g_params.userw, getpwuid(file->uid)->pw_name,
					g_params.groupw, getgrgid(file->gid)->gr_name,
					g_params.bytew, file->size, date, file->filename);
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
	copy = list;
	while (copy)
	{
		print_file(copy);
		copy = copy->next;
	}
}
