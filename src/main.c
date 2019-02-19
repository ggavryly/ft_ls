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
	int			flags;
	t_dir		*dir;
	t_info		*args;
	t_info		*head;

	dir = NULL;
	head = init_start(ar, av, &flags, args);
	args = head->next;
	while (args)
	{
		dir = allocate_dir(dir);
		path_manage(dir, args);
		init_info(flags, dir);
		sort(dir, flags);
		if (flags & R)
			dir->info->next = reverse_list(dir->info->next);
		display(dir, flags);
		args = args->next;
	}
	return (0);
}
