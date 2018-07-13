/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:15:30 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/07/13 11:15:30 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		throw_illegal_option(char f)
{
	ft_dprintf(2, "ft_ls: illegal option -- %c\n", f);
	ft_dprintf(2, "usage: ft_ls [-1adflrtuxCRUS] [file ...]\n");
	exit(1);
	return (0);
}

void	throw_generic_error(char *problem_name)
{
	ft_dprintf(2, "ft_ls: %s: %s\n", problem_name, strerror(errno));
}
