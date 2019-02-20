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

static t_info	*display_dir(t_dir *dir, int flags)
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
	else
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
		display_dir(dir, flags);
		if (dir->sub_d)
		{
			ft_putstr("\n");
			display_dirs(dir->sub_d, flags);
		}
		else
			ft_putstr("\n");
		dir = dir->next;
	}
	return (head);
}


t_dir			*display(t_dir *dir, int flags)
{
	if (flags & BIG)
	{
		dir->info = display_dir(dir, flags);
		ft_putstr("\n");
		dir = display_dirs(dir->sub_d, flags);
	}
	else if (!(flags & BIG))
	{
		dir->info = display_dir(dir, flags);
		ft_putstr("\n");
		dir = display_dirs(dir->sub_d, flags);
	}
	return (dir);
}
