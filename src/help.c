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

void		recursive(t_dir **h, t_dir **l, t_info **t, t_dir **dir)
{
	*h = *dir;
	*t = allocate_info(*t);
	*l = *h;
	(*dir)->stream = opendir((*dir)->info->path);
}

//void		close_recursive_help(t_dir **d, t_dir **h)
//{
//	(*d)->stream ? closedir((*d)->stream) : 1;
//	(*d)->stream = NULL;
//	while (!(*d)->stream && (*h)->stream)
//		*d = (*d)->prev;
//}

void		init_data(t_info **tmp_info, t_dire *tmp_dire, t_info **dir)
{
	add_path(*tmp_info, tmp_dire, *dir);
	init_stat(*tmp_info, tmp_dire);
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


t_info		*reverse_info(t_info *info)
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

t_dir		*reverse_dir(t_dir *info)
{
	t_dir	*head;
	t_dir	*curr;
	t_dir	*prev;
	t_dir	*next;

	head = info;
	curr = head;
	prev = NULL;
	while (curr)
	{
		curr->info->next = reverse_info(curr->info->next);
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head = prev;
	return (head);
}
