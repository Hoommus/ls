/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:15:35 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/07/13 11:15:35 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_file	*list_swap(t_file *list, t_file *first, t_file *second)
{
	t_file	swap;
	t_file	*firstnext;
	t_file	*secondnext;

	firstnext = first->next;
	secondnext = second->next;
	ft_memcpy(&swap, first, sizeof(t_file));
	ft_memcpy(first, second, sizeof(t_file));
	ft_memcpy(second, &swap, sizeof(t_file));
	first->next = firstnext;
	second->next = secondnext;
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
