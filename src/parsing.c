#include "../include/ft_ls.h"

int		get_flag(char f)
{
	if (f == 'l')
		return (F_LONG);
	else if (f == 'a')
		return (F_ALL);
	else if (f == 't')
		return (F_SORTT);
	else if (f == 'r')
		return (F_SORTR);
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
		if (str[i][0] != '-' || str[i][1] == '\0')
			break ;
		copy = str[i] + 1;
		while (*copy)
			g_flags |= get_flag(*copy++);
		i++;
	}
	return (i);
}
