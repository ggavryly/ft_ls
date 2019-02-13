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
	clock_t begin = clock();
	int 		flags;
	int 		tmp;
	t_dir		*dir;

	tmp	= init_option(ar, av, &flags);
	ar -= tmp + 1;
	av += tmp + 1;
	dir = allocate_dir(dir);
	path_manage(dir, av, ar);
	init_info(flags, dir);
	dir = display_dirs(dir);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	//system("leaks ft_ls");
	printf("%lf\n", time_spent);
}
