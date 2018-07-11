#include "../include/ft_ls.h"

char	*get_whereto(char *filename, struct stat *s, char *path)
{
	char	buf[1024];
	char	*whereto;
	char	*dummy;

	whereto = NULL;
	if (S_ISLNK(s->st_mode))
	{
		dummy = create_path(path, filename);
		ft_bzero(buf, 1024 * sizeof(char));
		readlink(dummy, buf, 1024);
		whereto = ft_strdup(buf);
	}
	return (whereto);
}

t_file	*create_file(struct stat *s, char *filename, char *path)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	if (new == NULL)
		return (NULL);
	new->full_name = create_path(path, filename);
	new->filename = ft_strdup(filename);
	new->path = ft_strdup(path);
	new->whereto = get_whereto(filename, s, path);
	new->blocks = s->st_blocks;
	new->atime = s->st_atimespec;
	new->ctime = s->st_ctimespec;
	new->mtime = s->st_mtimespec;
	new->btime = s->st_birthtimespec;
	new->links = s->st_nlink;
	new->mode = s->st_mode;
	new->size = s->st_size;
	new->uid = s->st_uid;
	new->gid = s->st_gid;
	new->dev = s->st_rdev;
	new->next = NULL;
	return (new);
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
	free(f->full_name);
	if (f->whereto != NULL)
		free(f->whereto);
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
