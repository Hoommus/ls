#include "../include/ft_ls.h"

char	**filter_errors(char **names, int argc)
{
	int			i;
	int			j;
	struct stat	s;
	char		**swap;

	swap = (char **)malloc(sizeof(char *) * (argc + 1));
	ft_bzero(swap, sizeof(char *) * (argc + 1));
	i = 0;
	j = 0;
	while (names[i])
	{
		if (stat(names[i], &s) != 0 || lstat(names[i], &s) != 0)
			ft_dprintf(2, "ft_ls: %s: %s\n", names[i], strerror(errno));
		else
			swap[j++] = names[i];
		i++;
	}
	return (swap);
}

void	scope_hack(char *name, struct stat *s, char *path, int is_lnk)
{
	static t_file	*head;
	static t_file	*tail;
	t_file			*copy;

	if (name != NULL)
	{
		if (is_lnk)
			lstat(name, s);
		list_add(&head, &tail, set_widths(create_file(s, name, path)));
	}
	else
	{
		copy = sort(head, get_sort());
		while (copy)
		{
			print_file(copy);
			copy = copy->next;
		}
		free_list(head);
		clear_widths();
	}
}

char	**filter_plain_files(char **names, int argc)
{
	int			j;
	int			sts;
	int			is_lnk;
	struct stat	s;
	char		**swap;

	swap = ft_memalloc(sizeof(char *) * (argc + 1));
	j = 0;
	while (*names)
	{
		sts = stat(*names, &s);
		is_lnk = is_link(*names);
		if (!needs_dir_treatment(*names, &s, &sts, &is_lnk)
			&& needs_file_treatment(*names, &s, &sts, &is_lnk))
		{
			scope_hack(*names, &s, "", is_lnk);
		}
		else
			swap[j++] = *names;
		names++;
	}
	scope_hack(NULL, &s, "", 0);
	return (swap);
}
