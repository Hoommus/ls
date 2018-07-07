#include "../include/ft_ls.h"

t_file				*sort(t_file *list, int (*f)(t_file *a, t_file *b))
{
	int i;

	list = list->next;
	i = f(list, list->next);
	return (list);
}

int					compare_by_name(t_file *a, t_file *b)
{
	return (ft_strcmp(a->filename, b->filename));
}
