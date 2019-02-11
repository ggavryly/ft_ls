/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:16:13 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/08 16:16:15 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void		init_default(t_dir *dir)
{
	t_info		*curr;
	t_info		*prev;
	t_dire		*tmp_dirent;

	prev = NULL;
	(dir->stream = opendir(dir->info->path)) ? NULL : error_procesing();
	while ((tmp_dirent = readdir(dir->stream)))
	{
		if (tmp_dirent->d_name[0] == '.')
			continue;
		curr = (t_info *)malloc(sizeof(t_info));
		ft_strcpy(curr->name, tmp_dirent->d_name);
		if (prev)
			prev->next = curr;
		else if (!prev)
			dir->info->next = curr;
		prev = curr;
		curr->next = NULL;
	}
}

static void		init_stat(t_dir *dir)
{
	t_st	*stat;
	stat = lstat(dir->info->path, &stat);
	dir->info->mode = stat->st_mode;
	dir->info->nlink = stat->st_nlink;
	dir->info->uid = stat->st_uid;
	dir->info->gid = stat->st_gid;
	dir->info->dev = stat->st_rdev;
	dir->info->size = stat->st_size;
	dir->info->atime = stat->st_atimespec;
	dir->info->mtime = stat->st_mtimespec;
	dir->info->ctime = stat->st_ctimespec;
}

static void		init_recursive(t_dir *dir)
{
	DIR		*stream;
	t_info	*curr;
	t_dir	*tmp_dir;
	t_dire	*tmp_dirent;

	tmp_dir = dir;
	(stream = opendir(dir->info->path)) ? NULL : error_procesing();
	dir->stream = stream;
	while (!readdir(dir->stream))
	{
		while ((tmp_dirent = readdir(stream)))
		{
			if (tmp_dirent->d_name[0] == '.')
				continue;
			inin_stat(curr);
			if (S_ISDIR(tmp_dir->info->mode))
			{
				stream = new_dir(tmp_dir);
				tmp_dir = tmp_dir->next;
			}
			else
				new_node(tmp_dir->info, tmp_dirent);
		}
	}
}


t_dir			*init_info(int flags, t_dir *dir)
{
	if (!flags)
		init_default(dir);
	else
	{
		if (flags & RR)
			init_recursive(dir);
//		if (flags & L || flags & A && flags & R || flags & T)
//			init_complex(dir);
	}
	return (dir);
}