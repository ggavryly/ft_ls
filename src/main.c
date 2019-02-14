/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 16:33:53 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/10 16:33:54 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		main(int ar, char **av)
{
	int 		flags;
	int 		tmp;
	t_dir		*dir;
	t_dir		*prev;

	prev = NULL;
	tmp	= init_option(ar, av, &flags);
	ar -= tmp + 1;
	av += tmp + 1;
	if (ar > 1)
		flags |= BIG;
	if (ar == 0)
		ar = 1;
	while (ar)
	{
		dir = allocate_dir(dir);
		path_manage(dir, av++, ar--);
		init_info(flags, dir);
		add_to_list_dir(dir, prev);
		prev = dir;
	}
	display(prev, flags);
	list_free(prev);
	return (0);
}
