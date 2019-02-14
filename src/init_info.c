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

static void		init_default(t_dir *dir, int *flags)
{
	t_info		*curr;
	t_info		*prev;
	t_dire		*tmp_dirent;

	prev = NULL;
	if (((dir->stream = opendir(dir->info->path)) ? (1) : (0)))
	{
		while ((tmp_dirent = readdir(dir->stream)))
		{
			if (tmp_dirent->d_name[0] == '.')
				continue;
			curr = (t_info *) malloc(sizeof(t_info));
			ft_strcpy(curr->name, tmp_dirent->d_name);
			if (prev)
				prev->next = curr;
			else if (!prev)
				dir->info->next = curr;
			prev = curr;
			curr->next = NULL;
		}
	}
}

static void		init_stat(t_info *tmp_inf, t_dire *tmp_dire)
{
	t_st	stat;

	lstat(tmp_inf->path, &stat);
	ft_strcpy(tmp_inf->name, tmp_dire->d_name);
	tmp_inf->mode = stat.st_mode;
	tmp_inf->nlink = stat.st_nlink;
	tmp_inf->uid = stat.st_uid;
	tmp_inf->gid = stat.st_gid;
	tmp_inf->dev = stat.st_rdev;
	tmp_inf->size = stat.st_size;
	tmp_inf->atime = stat.st_atimespec;
	tmp_inf->mtime = stat.st_mtimespec;
	tmp_inf->ctime = stat.st_ctimespec;
}

static void		init_recursive(t_dir *dir, int *flags)
{
	t_dir	*head;
	t_dir	*last;
	t_dire	*tmp_dirent;
	t_info	*tmp_info;

	if (((dir->stream = opendir(dir->info->path)) ? (1) : (0)))
	{
		head = dir;
		tmp_info = allocate_info(tmp_info);
		last = head;
		while (head->stream)
		{
			while ((tmp_dirent = readdir(dir->stream)))
			{
				if (tmp_dirent->d_name[0] == '.')
					continue;
				add_path(tmp_info, tmp_dirent, dir->info);
				init_stat(tmp_info, tmp_dirent);
				if (S_ISDIR(tmp_info->mode))
				{
					last = new_dir(last, tmp_info, dir);
					dir = last;
					if (!last->stream)
						break;
				}
				else
					new_node(dir, tmp_info);
			}
			dir->stream ? closedir(dir->stream) : 1;
			dir->stream = NULL;
			while (!dir->stream && head->stream)
				dir = dir->prev;
		}
	}
	free(tmp_info);
}


t_dir			*init_info(int flags, t_dir *dir)
{
	if (flags)
	{
		if (flags & RR)
			init_recursive(dir, &flags);
//		if (flags & L || flags & A && flags & R || flags & T)
//			init_complex(dir);
	}
	if (!flags || flags & BIG)
		init_default(dir, &flags);
	return (dir);
}