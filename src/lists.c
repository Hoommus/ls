#include "../include/ft_ls.h"

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
