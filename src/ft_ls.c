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

void	traverse_read_print(int size, char **names)
{
	int			i;
	struct stat	s;
	t_file		*list;

	i = 0;
	if (*names == NULL)
	{
		size = 1;
		*names = ".";
	}
	while (i < size && names[i])
	{
		if (stat(names[i], &s) == 0 && S_ISDIR(s.st_mode))
		{
			list = get_directory_contents(".", opendir("."));
			print_directory(list);
		}
		else
			ft_printf("ft_ls: %s: %s\n", names[i], strerror(errno));
		i++;
	}
}

int main(int argc, char **argv)
{
	int			f;

	f = parse_flags(argc - 1, ++argv);
	argc -= f;
	argv += f;
	traverse_read_print(argc, argv);
	return (0);
}

