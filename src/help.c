/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:44:24 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/18 22:44:26 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void	info_free(t_info *info)
{
	t_info *walk;
	t_info *next;

	walk = info;
	while (walk)
	{
		next = walk->next;
		free(walk);
		walk = next;
	}
}

void		list_free(t_dir *dir)
{
	dir->stream = NULL;
	dir->sub_d = NULL;
	dir->sub_u = NULL;
	dir->next = NULL;
	info_free(dir->info);
	dir->info = NULL;
	free(dir);
}

void		recursive(t_dir **h, t_dir **l, t_info **t, t_dir **dir)
{
	*h = *dir;
	*t = allocate_info(*t);
	*l = *h;
	(*dir)->stream = opendir((*dir)->info->path);
}

int			scip_dot(t_dire *tmp_dire, int flags)
{
	if (tmp_dire->d_name[0] == '.')
	{
		if (flags & A)
			return (0);
		return (1);
	}
	return (0);
}

t_info		*reverse_dir(t_info *info)
{
	t_info	*head;
	t_info	*curr;
	t_info	*prev;
	t_info	*next;

	head = info;
	curr = head;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head = prev;
	return (head);
}
