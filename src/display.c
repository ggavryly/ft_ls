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

static t_info	*display_first(t_dir *dir, int flags)
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

static t_dir	*display_dirs_first(t_dir *dir, int flags)
{
	t_dir	*head;

	head = dir;
	if (!head)
		return (NULL);
	head->info = display_first(head, flags);
	if (head->next)
		write(1, "\n", 1);
	head = head->next;
	while (head)
	{
		ft_putstr(head->info->path);
		write(1, ":\n", 2);
		head->info = display_first(head, flags);
		if (head->next)
			write(1, "\n", 1);
		head = head->next;
	}
	return (dir);
}

static t_dir	*display_dirs_default(t_dir *dir, int flags)
{
	t_dir	*head;

	head = dir;
	if (!head)
		return (NULL);
	while (head)
	{
		ft_putstr(head->info->path);
		write(1, ":\n", 2);
		head->info = display_first(head, flags);
		if (head->next)
			write(1, "\n", 1);
		head = head->next;
	}
	return (dir);
}

t_dir	*display(t_dir *dir, int flags)
{
	if (flags & BIG)
		dir = display_dirs_default(dir, flags);
	else if (!(flags & BIG))
		dir = display_dirs_first(dir, flags);
	return (dir);
}
