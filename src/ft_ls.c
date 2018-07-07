#include "../include/ft_ls.h"

int		get_flag(char f)
{
	if (f == 'l')
		return (F_LONG);
	else if (f == 'a')
		return (F_ALL);
	else if (f == 't')
		return (4);
	else if (f == 'r')
		return (8);
	else if (f == 'R')
		return (F_RECUR);
	else if (f == 'G')
		return (F_COLOR);
	else if (f == 'i')
		return (64);
	else if (f == 'f')
		return (F_NSORT);
	else
		return (throw_illegal_option(f));
}

int		parse_flags(int count, char **str)
{
	int		i;
	char	*copy;

	i = 0;
	while (i < count)
	{
		if (str[i][0] != '-')
			break ;
		copy = str[i] + 1;
		while (*copy)
			g_flags |= get_flag(*copy++);
		i++;
	}
	return (i);
}

char	**get_filenames(char *dirname, t_file *list)
{
	char	**array;
	t_file	*swap;
	int		i;

	i = 0;
	swap = list;
	while (swap && ++i)
		swap = swap->next;
	if (g_flags & F_ALL)
		i -= 2;
	array = (char **)malloc(sizeof(char *) * i + 1);
	array[i] = NULL;
	i = 0;
	while (list)
	{
		if (!(IS_CURR(list->filename) || IS_PARENT(list->filename)))
			array[i++] = create_path(dirname, list->filename);
		list = list->next;
	}
	return (array);
}

void	read_dir(char *dirname)
{
	char		**filenames;
	DIR			*dir;
	t_file		*list;

	list = NULL;
	clear_widths();
	dir = opendir(dirname);
	if (dir == NULL)
		ft_printf("ft_ls: %s: %s\n", dirname, strerror(errno));
	else
		list = get_directory_contents(dirname, dir);
	if (list != NULL)
		print_directory(list);
	else
		ft_printf("\n%s:\n", dirname);
	if ((g_flags & F_RECUR))
	{
		filenames = get_filenames(dirname, list);
		stat_read_print(filenames);
		free_array(filenames);
	}
	free_list(list);
}

void	stat_read_print(char **names)
{
	int			i;
	struct stat	s;
	t_file		*list;

	i = -1;
	while (names[++i])
		if (stat(names[i], &s) == 0 && S_ISDIR(s.st_mode))
		{
			if ((IS_CURRENT(names[i]) || IS_PARENT(names[i])))
				continue ;
			read_dir(names[i]);
		}
		else if ((stat(names[i], &s) == 0 && !S_ISDIR(s.st_mode))
				|| (IS_CURRENT(names[i]) || IS_PARENT(names[i])))
		{
			if (ft_strchr(names[i], '/') != NULL)
				continue ;
			list = sort(create_file(names[i], &s, ""), get_sort());
			print_file(list);
			free_file(list);
		}
		else
			ft_printf("ft_ls: %s: %s\n", names[i], strerror(errno));
}

int		main(int argc, char **argv)
{
	++argv;
	argv += parse_flags(argc - 1, argv);
	if (*argv == NULL)
		*(--argv) = ".";
	stat_read_print(argv);
//	system("leaks --fullStacks --fullContent --hex ft_ls");
	return (0);
}

