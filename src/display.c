/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:34:40 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/07 15:34:44 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_info			*display_dir(t_dir *dir, int flags)
{
	t_info *head;

	head = dir->info;
	if (flags & L)
		total_put(dir->info->next);
	if (dir->info->next)
	{
		while (dir->info->next)
		{
			if (flags & L)
				flag_l(dir->info->next);
			else
			{
				ft_putstr(dir->info->next->name);
				write(1, "\n", 1);
			}
			dir->info = dir->info->next;
		}
	}
	else if (dir->info->error_num)
		put_error(dir);
	return (head);
}

static	t_dir	*display_dirs(t_dir *dir, int flags)
{
	t_dir	*head;

	head = dir;
	while (dir)
	{
		ft_putstr(dir->info->path);
		ft_putstr(":\n");
		dir->info = display_dir(dir, flags);
		if (dir->sub_d)
		{
			ft_putstr("\n");
			dir->sub_d = display_dirs(dir->sub_d, flags);
		}
		if (dir->next)
			ft_putstr("\n");
		dir = dir->next;
	}
	return (head);
}

t_dir			*display(t_dir *dir, int *flags)
{
	if (*flags & BIG)
	{
		ft_putstr(dir->info->path);
		ft_putstr(":\n");
		dir->info = display_dir(dir, *flags);
	}
	else
	{
		*flags |= BIG;
		dir->info = display_dir(dir, *flags);
	}
	return (dir);
}
