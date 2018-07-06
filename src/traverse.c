#include "../include/ft_ls.h"

t_file	*get_directory_contents(char *dirname, DIR *dir)
{
	t_file			*single;
	t_file			*list_head;
	t_file			*list_tail;
	struct stat		st;
	struct dirent	*entity;

	list_head = NULL;
	list_tail = NULL;
	if (dir == NULL)
		ft_printf("ft_ls: %s: %s\n", dirname, strerror(errno));
	while ((entity = readdir(dir)) != NULL)
	{
		if (stat(entity->d_name, &st) == 0)
		{
			if (entity->d_name[0] == '.' && (g_flags & 2) != 2)
				continue ;
			single = set_widths(create_file(entity->d_name, &st));
			list_add(&list_head, &list_tail, single);
		}
		else
			ft_printf("ft_ls: %s: %s\n", dirname, strerror(errno));
	}
	closedir(dir);
	return (list_head);
}

