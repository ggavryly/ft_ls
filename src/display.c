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

void	display(void)
{
}

void	display_default(t_dir *dir)
{
	while (dir->info)
	{
		ft_putstr(dir->info->name);
		write(1,"\n", 1);
		dir->info = dir->info->next;
	}
}

t_dir	*display_dirs(t_dir *dir)
{
	t_dir *head;

	head = dir;
	if (!head)
		return (NULL);
	while (head)
	{
		ft_putstr(head->info->path);
		write(1, ":\n", 2);
		head->info = head->info->next;
		display_default(head);
		write(1, "\n", 1);
		head = head->next;
	}
	return (dir);
}