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

void		init_stat(t_info *tmp_inf, t_dire *tmp_dire)
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
	if (((dir->stream = opendir(dir->info->path)) ? (1) : (0)))
	{
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
}

static void		init_recursive(t_dir *dir, int *flags)
{
	t_dir	*head;
	t_dir	*last;
	t_dire	*d;
	t_info	*tmp;

	init_recursive_help(&head, &last, &tmp, &dir);
	while (head->stream)
	{
		while ((d = readdir(dir->stream)))
		{
			if (scip_dot(d, *flags))
					continue;
			init_data(&tmp, d, &dir->info);
			if (S_ISDIR(tmp->mode) && ft_strcmp(d->d_name, ".") &&
			ft_strcmp(d->d_name, ".."))
			{
				last = new_dir(last, tmp, &dir);
				if (!last->stream)
					break;
			}
			else
				new_node(dir, tmp);
		}
		close_recursive_help(&dir, &head);
	}
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