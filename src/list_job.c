/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 20:27:47 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/07 20:27:48 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	add_info(t_dir *last, t_info *add_info)
{
	t_info *last_info;
	t_info *tmp;

	last_info = NULL;
	tmp = last->info;
	while (tmp)
	{
		last_info = tmp;
		tmp = tmp->next;
	}
	if (last_info)
		last_info->next = add_info;
}

void	new_node(t_dir *dir, t_info *tmp_info)
{
	t_info *new;

	new = NULL;
	new = allocate_info(new);
	ft_strcpy(new->name, tmp_info->name);
	ft_strcpy(new->path, tmp_info->path);
	new->blocks = tmp_info->blocks;
	new->mode = tmp_info->mode;
	new->nlink = tmp_info->nlink;
	new->uid = tmp_info->uid;
	new->gid = tmp_info->gid;
	new->dev = tmp_info->dev;
	new->size = tmp_info->size;
	new->atime = tmp_info->atime;
	new->mtime = tmp_info->mtime;
	new->ctime = tmp_info->ctime;
	add_info(dir, new);
}

void	info_copy(t_info *dst, t_info *tmp_info)
{
	ft_strcpy(dst->path, tmp_info->path);
	ft_strcpy(dst->name, tmp_info->name);
	dst->blocks = tmp_info->blocks;
	dst->mode = tmp_info->mode;
	dst->nlink = tmp_info->nlink;
	dst->uid = tmp_info->uid;
	dst->gid = tmp_info->gid;
	dst->dev = tmp_info->dev;
	dst->size = tmp_info->size;
	dst->atime = tmp_info->atime;
	dst->mtime = tmp_info->mtime;
	dst->ctime = tmp_info->ctime;
}

t_dir	*new_dir(t_dir *sub_d, t_info *dir_info, t_dir *sub_u, t_dir **head)
{
	t_dir	*new;

	new = NULL;
	new = allocate_dir(new);
	info_copy(new->info, dir_info);
	new->sub_u = sub_u;
	if (sub_d)
		sub_d->next = new;
	else
		*head = new;
	return (new);
}
