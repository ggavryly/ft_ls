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

void			init_stat(t_info *tmp_inf, t_dire *tmp_dire)
{
	t_st	stat_tmp;

	lstat(tmp_inf->path, &stat_tmp);
	ft_strcpy(tmp_inf->name, tmp_dire->d_name);
	tmp_inf->blocks = stat_tmp.st_blocks;
	tmp_inf->mode = stat_tmp.st_mode;
	tmp_inf->nlink = stat_tmp.st_nlink;
	tmp_inf->uid = stat_tmp.st_uid;
	tmp_inf->gid = stat_tmp.st_gid;
	tmp_inf->dev = stat_tmp.st_rdev;
	tmp_inf->size = stat_tmp.st_size;
	tmp_inf->atime = stat_tmp.st_atimespec;
	tmp_inf->mtime = stat_tmp.st_mtimespec;
	tmp_inf->ctime = stat_tmp.st_ctimespec;
}

static void		init_default(t_dir *dir, int *flags)
{
	t_info		*curr;
	t_info		*head;
	t_info		*prev;
	t_dire		*tmp_d;

	head = dir->info;
	prev = NULL;
	curr = NULL;
	dir->stream = opendir(dir->info->path);
	while ((tmp_d = readdir(dir->stream)))
	{
		if (tmp_d->d_name[0] == '.' && !(*flags & A))
			continue;
		curr = allocate_info(curr);
		ft_strcpy(curr->path, dir->info->path);
		ft_strcat(curr->path, "/");
		ft_strcat(curr->path, tmp_d->d_name);
		init_stat(curr, tmp_d);
		if (prev)
			prev->next = curr;
		head->next = curr;
		head = head->next;
		prev = curr;
	}
	closedir(dir->stream);
}

static t_dir	*check_dir(t_dir *dir)
{
	t_info	*walk;
	t_dir	*sub_d_head;
	t_dir	*sub_d_last;

	walk = dir->info;
	sub_d_head = NULL;
	sub_d_last = NULL;
	while (walk)
	{
		if (S_ISDIR(walk->mode))
			sub_d_last = new_dir(sub_d_last, walk, dir, &sub_d_head);
		walk = walk->next;
	}
	closedir(dir->stream);
	dir->stream = NULL;
	return (sub_d_head);
}

static void		init_recursive(t_dir *dir, int *flags)
{
	t_dir	*head;
	t_dir	*sub_d;
	t_dir	*sub_d_first;
	t_dire	*d;
	t_info	*tmp;

	recursive(&head, &sub_d, &tmp, &dir);
	while (head)
	{
		while ((d = readdir(sub_d->stream)))
		{
			if (scip_dot(d, *flags))
				continue ;
			init_data(&tmp, d, &sub_d->info);
			new_node(sub_d, tmp);
		}
		sort(sub_d, *flags);
		if (!sub_d->next)
		{
			sub_d = head;
			sub_d = check_dir(sub_d);
		}
		else
			sub_d = sub_d->next;
		if (sub_d)
		{
			while (sub_d)
			{
				if ((sub_d->stream = opendir(sub_d->info->path)) ? 1 : open_error(&sub_d))
					break;
				else
					sub_d = sub_d->next;
			}
			if (!sub_d)
				sub_d = sub_d->sub_u;
		}
	}
	free(tmp);
}

t_dir			*init_info(int flags, t_dir *dir)
{
	if (flags & RR)
	{
		if (flags & RR || flags & A)
			init_recursive(dir, &flags);
	}
	else
		init_default(dir, &flags);
	return (dir);
}
