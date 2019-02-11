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
	if (!dir)
		return;
	dir->info = dir->info->next;
	while (dir->info)
	{
		ft_putstr(dir->info->name);
		write(1,"\n", 1);
		dir->info = dir->info->next;
	}
}