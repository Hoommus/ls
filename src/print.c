#include "../include/ft_ls.h"

void	print_file(t_file *file)
{
	if (g_flags & 1)
		ft_printf("%s %*u %-*s %-*s %*lld %s %s\n",
				get_readable_mode(file->mode), g_params.linkw, file->links,
				g_params.userw, file->uid_s, g_params.groupw, file->gid_s,
				g_params.bytew, file->size,
				ft_strsub(ctime(&(file->mtime.tv_sec)), 4, 12),
				file->filename);
	else
		ft_printf("%s\t\n", file->filename);
}

void	print_directory(t_file *list)
{
	t_file	*copy;

	copy = list;
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