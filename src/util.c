#include "../include/ft_ls.h"

char	*create_path(char *oldpath, char *filename)
{
	char	*full;

	//if (ft_strlen(oldpath) == 1 && oldpath[0] != '/')
		oldpath = ft_strjoin(oldpath, "/");
	full = ft_strjoin(oldpath, filename);
	//if (ft_strlen(oldpath) == 1 && oldpath[0] != '/')
		free(oldpath);
	return (full);
}

t_file	*create_file(char *filename, struct stat *s, char *path)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	if (new == NULL)
		return (NULL);
	new->filename = ft_strdup(filename);
	new->path = ft_strdup(path);
	new->blocks = s->st_blocks;
	new->links = s->st_nlink;
	new->atime = s->st_atimespec;
	new->mtime = s->st_mtimespec;
	new->ctime = s->st_ctimespec;
	new->btime = s->st_birthtimespec;
	new->mode = s->st_mode;
	new->size = s->st_size;
	new->uid = s->st_uid;
	new->gid = s->st_gid;
	new->next = NULL;
	return (new);
}



t_file	*set_widths(t_file *single)
{
	int		nbrlen;
	char	*user;
	char	*group;

	user = getpwuid(single->uid)->pw_name;
	group = getgrgid(single->gid)->gr_name;
	nbrlen = ft_nbrlen(single->size);
	if (g_params.bytew < nbrlen)
		g_params.bytew = nbrlen;
	nbrlen = ft_nbrlen(single->links);
	if (g_params.linkw < nbrlen)
		g_params.linkw = nbrlen;
	nbrlen = ft_strlen(group);
	if (g_params.groupw < nbrlen)
		g_params.groupw = nbrlen + 1;
	nbrlen = ft_strlen(user);
	if (g_params.userw < nbrlen)
		g_params.userw = nbrlen + 1;
	return (single);
}

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_file(t_file *f)
{
	free(f->path);
	free(f->filename);
	free(f);
}

void	free_list(t_file *list)
{
	t_file	*swap;
	t_file	*temp;

	swap = list;
	while (swap)
	{
		temp = swap->next;
		free_file(swap);
		swap = temp;
	}
}
