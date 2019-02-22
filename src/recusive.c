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

static t_dir	*sub_unext(t_dir *walk)
{
	t_dir	*result;

	result = NULL;
	while (!result)
	{
		result = walk->sub_u;
		if (!result)
			break ;
		if (!result->next)
		{
			result = result->next;
			walk = walk->sub_u;
			continue ;
		}
		else
			return (result->next);
	}
	return (result);
}

static t_dir	*open_catalog(t_dir *w)
{
	t_dir *walk_sub_u;

	if (w)
	{
		walk_sub_u = sub_unext(w);
		while (w)
		{
			if ((w->stream = opendir(w->info->path)) ? (0) : !open_error(&w))
				w = w->next;
			else
				break ;
		}
		if (!w)
			w = open_catalog(walk_sub_u);
	}
	return (w);
}

static	t_dir	*sub_up(t_dir *dir)
{
	if (dir)
	{
		if (dir->next)
			return (dir->next);
		else
			dir = sub_up(dir->sub_u);
	}
	return (dir);
}

void			recursive_help(t_dir **w, t_dir **s, t_dir **next, int *flags)
{
	sort(*w, *flags);
	closedir((*w)->stream);
	*next = (*w)->next;
	*s = (*w)->sub_u;
	*w = check_dir(*w);
	if (!(*w))
	{
		*w = *next;
		if (!(*w))
			*w = sub_up(*s);
	}
	*w = open_catalog(*w);
}
