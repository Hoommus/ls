#include "../include/ft_ls.h"

void	clear_widths(void)
{
	g_params.namew = 0;
	g_params.groupw = 0;
	g_params.bytew = 0;
	g_params.linkw = 0;
	g_params.userw = 0;
}

t_file	*get_directory_contents(char *dirname, DIR *dir)
{
	char			*full_path;
	t_file			*list_head;
	t_file			*list_tail;
	struct stat		st;
	struct dirent	*entity;

	list_head = NULL;
	list_tail = NULL;
	if (dir == NULL)
		return (list_head);
	while ((entity = readdir(dir)) != NULL)
	{
		if (stat(full_path = create_path(dirname, entity->d_name), &st) == 0)
		{
			if (!(entity->d_name[0] == '.' && (g_flags & 2) != 2))
				list_add(&list_head, &list_tail, set_widths(
					create_file(entity->d_name, &st, dirname)));
		}
		else
			ft_printf("ft_ls: %s: %s\n", dirname, strerror(errno));
		free(full_path);
	}
	closedir(dir);
	return (list_head);
}
