#include "../include/ft_ls.h"

int		get_flag(char f)
{
	if (f == 'l')
		return (1);
	else if (f == 'a')
		return (2);
	else if (f == 't')
		return (4);
	else if (f == 'r')
		return (8);
	else if (f == 'R')
		return (16);
	else if (f == 'G')
		return (32);
	else if (f == 'i')
		return (64);
	else if (f == 'f')
		return (128);
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
	array = (char **)malloc(sizeof(char *) * i + 1);
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
	t_file		*list;

	list = get_directory_contents(dirname, opendir(dirname));
	print_directory(list);
	if (g_flags & F_RECUR)
	{
//		while (copy && S_ISDIR(copy->mode))
//		{
			filenames = get_filenames(dirname, list);
			traverse_read_print(filenames);
			free_array(filenames);
			//copy = copy->next;
//		}
	}
	free_list(list);
}

void	traverse_read_print(char **names)
{
	int			i;
	struct stat	s;
	t_file		*list;

	i = -1;
	while (names[++i])
		if (stat(names[i], &s) == 0 && S_ISDIR(s.st_mode))
		{
			read_dir(names[i]);
		}
		else if (stat(names[i], &s) == 0 && !S_ISDIR(s.st_mode))
		{
			if (ft_strrchr(names[i], '/') != NULL)
				continue ;
			list = create_file(names[i], &s, "");
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
	traverse_read_print(argv);
//	system("leaks --fullStacks --fullContent --hex ft_ls");
	return (0);
}

