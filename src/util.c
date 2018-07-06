#include "../include/ft_ls.h"

t_file	*create_file(char *filename, struct stat *s)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	if (new == NULL)
		return (NULL);
	new->filename = ft_strdup(filename);
	new->links = s->st_nlink;
	new->mode = s->st_mode;
	new->atime = s->st_atimespec;
	new->mtime = s->st_mtimespec;
	new->ctime = s->st_ctimespec;
	new->btime = s->st_birthtimespec;
	new->size = s->st_size;
	new->blocks = s->st_blocks;
	new->uid = s->st_uid;
	new->gid = s->st_gid;
	new->uid_s = ft_strdup(getpwuid(new->uid)->pw_name);
	new->gid_s = ft_strdup(getgrgid(new->gid)->gr_name);
	new->next = NULL;
	return (new);
}

t_file	*set_widths(t_file *single)
{
	int		nbrlen;

	nbrlen = ft_nbrlen(single->size);
	if (g_params.bytew < nbrlen)
		g_params.bytew = nbrlen;
	nbrlen = ft_nbrlen(single->links);
	if (g_params.linkw < nbrlen)
		g_params.linkw = nbrlen;
	nbrlen = ft_strlen(single->filename);
	if (g_params.namew < nbrlen)
		g_params.namew = nbrlen;
	nbrlen = ft_strlen(single->gid_s);
	if (g_params.groupw < nbrlen)
		g_params.groupw = nbrlen + 1;
	nbrlen = ft_strlen(single->uid_s);
	if (g_params.userw < nbrlen)
		g_params.userw = nbrlen + 1;
	return (single);
}

t_file	*list_swap(t_file *list, t_file *first, t_file *second)
{
	t_file	*copy;

	copy = list;
	while (copy->next != first)
		copy = copy->next;
	copy->next = second;
	first->next = second->next;
	second->next = first;
	return (list);
}

void	list_add(t_file **head, t_file **tail, t_file *to_add)
{
	if (*head == NULL)
		*head = to_add;
	else if (*tail == NULL)
	{
		*tail = to_add;
		(*head)->next = *tail;
	}
	else
	{
		(*tail)->next = to_add;
		(*tail) = (*tail)->next;
	}
}

void	free_file(t_file *f)
{
	free(f->uid_s);
	free(f->gid_s);
	free(f->filename);
	free(f);
}