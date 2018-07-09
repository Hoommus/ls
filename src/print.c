#include "../include/ft_ls.h"

void	print_file(t_file *file)
{
	char	*date;
	char	*mode;

	mode = get_readable_mode(file->mode);
	date = ft_strsub(ctime(&(file->mtime.tv_sec)), 4, 12);
	if (g_flags & 1)
		ft_printf("%s %*u %-*s %-*s %*lld %s %s\n",
				mode, g_params.linkw, file->links,
				g_params.userw,  getpwuid(file->uid)->pw_name,
				g_params.groupw, getgrgid(file->gid)->gr_name,
				g_params.bytew, file->size, date, file->filename);
	else
		ft_printf("%s \n", file->filename);
	free(date);
	free(mode);
}

void	print_directory(t_file *list)
{
	t_file	*copy;

	copy = list;
	if ((g_flags & F_RECUR) && list != NULL && !IS_CURR(list->path))
		ft_printf("\n%s:\n", list->path);
	if ((g_flags & F_LONG) && copy != NULL)
		print_total(list);
	while (copy)
	{
		print_file(copy);
		copy = copy->next;
	}
}

void	print_total(t_file *list)
{
	t_file	*copy;
	size_t	total;

	total = 0;
	copy = list;
	while (copy)
	{
		total += copy->blocks;
		copy = copy->next;
	}
	ft_printf("total: %zu\n", total);
}