/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recusive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:41:20 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/21 10:41:21 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static t_dir	*check_dir(t_dir *dir)
{
	t_info	*walk;
	t_dir	*sub_d_head;
	t_dir	*sub_d_last;

	walk = dir->info->next;
	sub_d_head = NULL;
	sub_d_last = NULL;
	while (walk)
	{
		if (S_ISDIR(walk->mode))
		{
			if (ft_strcmp(walk->name, ".") && ft_strcmp(walk->name, ".."))
				sub_d_last = new_dir(sub_d_last, walk, dir, &sub_d_head);
		}
		walk = walk->next;
	}
	if (sub_d_head)
		dir->stream = NULL;
	dir->sub_d = sub_d_head;
	return (sub_d_head);
}

static t_dir	*walk_list(t_dir *w, int flags, t_dir *next, int mode)
{
	while (w && mode != 2)
	{
		next = w->next;
		if (mode == 1)
			list_free(w);
		w = ((mode == 0) ? (w) : (next));
		if (!w)
			break ;
		if ((w->stream = opendir(w->info->path)) ? (0) : !open_error(&w, flags))
		{
			next = w->next;
			list_free(w);
			w = next;
		}
		else
			break ;
	}
	return (w);
}

static t_dir	*open_catalog(t_dir *w, int flags, int mode)
{
	t_dir *walk_sub_u;
	t_dir *next;

	next = NULL;
	if (w)
	{
		walk_sub_u = w->sub_u;
		w = walk_list(w, flags, next, mode);
		if (!w || mode == 2)
		{
			if (w)
				list_free(w);
			w = open_catalog(walk_sub_u, flags, 1);
		}
	}
	return (w);
}

void			recursive_help(t_dir **w, t_dir **s, t_dir **next, int *flags)
{
	t_dir *prev;

	sort(*w, *flags);
	prev = *w;
	closedir((*w)->stream);
	(*w) = display(*w, flags);
	*next = (*w)->next;
	*s = *w;
	*w = check_dir(*w);
	if (!(*w))
	{
		*w = *next;
		if (!(*w))
			*w = open_catalog(*s, *flags, 2);
		else
		{
			list_free(prev);
			*w = open_catalog(*w, *flags, 0);
		}
	}
	else
		*w = open_catalog(*w, *flags, 0);
	if (*w)
		ft_putchar('\n');
}

void			info_to_null(t_info *info)
{
	info->error_num = 0;
	info->mode = 0;
	info->nlink = 0;
	info->uid = 0;
	info->gid = 0;
	info->dev = 0;
	info->size = 0;
	info->blocks = 0;
}
