/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 20:44:20 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/07 20:44:21 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_dir	*allocate_dir(t_dir *dir)
{
	((dir = (t_dir *)malloc(sizeof(t_dir)))) ? (1) : error_procesing();
	((dir->info = (t_info *)malloc(sizeof(t_info)))) ? (1) : error_procesing();
	dir->stream = NULL;
	dir->info->next = NULL;
	dir->next = NULL;
	dir->prev = NULL;
	return (dir);
}

t_info	*allocate_info(t_info *info)
{
	(info = (t_info *)malloc(sizeof(t_info))) ? (1) : error_procesing();
	info->next = NULL;
	return (info);
}

void	path_manage(t_dir *dir, char **av, int ar)
{
	if (!ar)
	{
		ft_strcpy(dir->info->name, ".");
		ft_strcpy(dir->info->path, ".");
	}
	else if (*av)
		ft_strcpy(dir->info->path, *av);
}

