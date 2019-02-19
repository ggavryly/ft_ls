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
	((dir = (t_dir *)malloc(sizeof(t_dir)))) ? (1) :
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	((dir->info = (t_info *)malloc(sizeof(t_info)))) ? (1) :
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	dir->stream = NULL;
	dir->sub_d = NULL;
	dir->sub_u = NULL;
	dir->info->next = NULL;
	dir->next = NULL;
	return (dir);
}

t_info	*allocate_info(t_info *info)
{
	(info = (t_info *)malloc(sizeof(t_info))) ? (1) :
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	info->next = NULL;
	return (info);
}

void	add_path(t_info *dst, t_dire *curr_dire, t_info *list)
{
	ft_strcpy(dst->path, list->path);
	ft_strcat(dst->path, "/");
	ft_strcat(dst->path, curr_dire->d_name);
}

void	path_manage(t_dir *dir, t_info *curr_ar)
{
	ft_strcpy(dir->info->path, curr_ar->path);
	ft_strcpy(dir->info->name, curr_ar->path);
}

void	free_path(char **path_ar)
{
	int	i;

	i = 0;
	while (path_ar[i])
		free(path_ar[i++]);
	free(path_ar);
}
