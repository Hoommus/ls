#include "../include/ft_ls.h"

char	**get_filenames(char *dirname, t_file *list)
{
	char	**array;
	t_file	*swap;
	int		i;

	i = 0;
	swap = list;
	while (swap && ++i)
		swap = swap->next;
	array = (char **)malloc(sizeof(char *) * (i + 1));
	array[i] = NULL;
	i = 0;
	while (list)
	{
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
	{
		list = sort(get_directory_contents(dirname, dir), get_sort());
		closedir(dir);
	}
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

int		is_link(char *name)
{
	char		buf[1024];

	if (readlink(name, buf, 1024) != -1)
		return (1);
	return (0);
}

void	stat_read_print(char **names)
{
	int			i;
	int			status;
	int			is_lnk;
	struct stat	s;
	t_file		*list;

	i = -1;
	while (names[++i])
		if (!(is_lnk = is_link(names[i])) && !(does_cycle(names[i]))
			&& (status = stat(names[i], &s)) == 0 && S_ISDIR(s.st_mode))
			read_dir(names[i]);
		else if ((status == 0 && (!S_ISDIR(s.st_mode) || does_cycle(names[i])))
				|| (is_lnk && (status == lstat(names[i], &s)) == 0))
		{
			if (!is_lnk && ft_strchr(names[i], '/') != NULL)
				continue;
			if (S_ISLNK(s.st_mode))
				lstat(names[i], &s);
			print_file(list = sort(create_file(&s, names[i], ""), get_sort()));
			free_file(list);
		}
		else if (status != 0)
			ft_printf("ft_ls: %s: %s\n", names[i], strerror(errno));
}

int		main(int argc, char **argv)
{
	struct winsize	term;

	++argv;
	argv += parse_flags(argc - 1, argv);
	if (*argv == NULL)
		*(--argv) = ".";
	ioctl(1, TIOCGWINSZ, &term);
	g_param.ttyw = term.ws_col;
	stat_read_print(argv);
//	system("leaks --fullStacks --fullContent --hex ft_ls");
	return (0);
}
