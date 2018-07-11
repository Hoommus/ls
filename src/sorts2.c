#include "../include/ft_ls.h"

int				compare_by_mtime(t_file *a, t_file *b)
{
	return (((g_flags & F_SORTR ? -1 : 1) *
			 (a->mtime.tv_sec - b->mtime.tv_sec)) > 0);
}

int				compare_by_ctime(t_file *a, t_file *b)
{
	return (((g_flags & F_SORTR ? -1 : 1) *
			 (a->ctime.tv_sec - b->ctime.tv_sec)) > 0);
}

int				compare_by_atime(t_file *a, t_file *b)
{
	return (((g_flags & F_SORTR ? -1 : 1) *
			 (a->atime.tv_sec - b->atime.tv_sec)) > 0);
}
