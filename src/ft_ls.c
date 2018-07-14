/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:14:58 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/07/14 11:02:56 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else if (dir != NULL)
		ft_printf("\n%s:\n", dirname);
	if ((g_flags & F_RECUR))
	{
		filenames = get_filenames(dirname, list);
		stat_read_print(filenames);
		free_array(filenames);
	}
	free_list(list);
}

int		isp(char *name)
{
	if (ft_strstr(name, "../"))
		return (1);
	return (0);
}

void	stat_read_print(char **names)
{
	int			i;
	int			sts;
	int			is_lnk;
	struct stat	s;
	t_file		*list;

	i = -1;
	while (names[++i])
	{
		if (needs_dir_treatment(names[i], &s, &sts, &is_lnk))
			read_dir(names[i]);
		else if (needs_file_treatment(names[i], &s, &sts, &is_lnk))
		{
			if ((!is_lnk && ft_strchr(names[i], '/') != NULL) || !isp(names[i]))
				continue;
			else if (is_lnk && isp(names[i]))
				lstat(names[i], &s);
			print_file(list = sort(create_file(&s, names[i], ""), get_sort()));
			free_file(list);
		}
		else if (sts != 0)
			ft_printf("ft_ls: %s: %s\n", names[i], strerror(errno));
	}
}

int		main(int argc, char **argv)
{
	struct winsize	term;
	char			**swap;

	++argv;
	argv += parse_flags(argc - 1, argv);
	if (*argv == NULL)
		*(--argv) = ".";
	if (ioctl(1, TIOCGWINSZ, &term) == -1 || term.ws_col == 0)
		g_flags |= F_ONEPER;
	g_param.ttyw = term.ws_col;
	argv = filter_errors(argv, argc);
	swap = argv;
	argv = filter_plain_files(argv, argc);
	free(swap);
	stat_read_print(argv);
	free(argv);
	return (0);
}
