#include "../include/ft_ls.h"

char	*create_path(char *oldpath, char *filename)
{
	char	*full;

	oldpath = ft_strjoin(oldpath, "/");
	full = ft_strjoin(oldpath, filename);
	free(oldpath);
	return (full);
}

void	set_dev_width(t_file *single)
{
	int		nbrlen;

	if (single->dev)
	{
		nbrlen = ft_nbrlen(major(single->dev));
		if (g_params.majorw < nbrlen)
			g_params.majorw = nbrlen;
		nbrlen = ft_nbrlen(minor(single->dev));
		if (g_params.minorw < nbrlen)
			g_params.minorw = nbrlen;
	}
}

t_file	*set_widths(t_file *single)
{
	int		nbrlen;
	char	*user;
	char	*group;

	user = getpwuid(single->uid)->pw_name;
	group = getgrgid(single->gid)->gr_name;
	if (g_params.bytew < (nbrlen = ft_nbrlen(single->size)))
		g_params.bytew = nbrlen;
	if (g_params.linkw < (nbrlen = ft_nbrlen(single->links)))
		g_params.linkw = nbrlen;
	if (g_params.groupw < (nbrlen = ft_strlen(group)))
		g_params.groupw = nbrlen + 1;
	if (g_params.userw < (nbrlen = ft_strlen(user)))
		g_params.userw = nbrlen + 1;
	if (g_params.ttycolumnw < (nbrlen = ft_strlen(single->filename)))
		g_params.ttycolumnw = nbrlen + 1;
	set_dev_width(single);
	return (single);
}

/*
** Yet another crutch, u know
*/

int		does_cycle(char *pth)
{
	size_t	i;

	i = ft_strlen(pth);
	if (i < 3)
		return (0);
	if ((pth[i - 2] == '/' && pth[i - 1] == '.' && pth[i] == '\0')
		|| (pth[i - 3] == '/' && pth[i - 2] == '.' && pth[i - 1] == '.')
		|| (pth[i - 2] == '/' && pth[i - 1] == '.' && !ft_isalnum(pth[i])))
	{
		return (1);
	}
	return (0);
}
