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

//t_dir	*check_dir(t_dir *dir)
//{
//	t_info	*walk;
//	t_dir	*sub_d_head;
//	t_dir	*sub_d_last;
//
//	walk = dir->info->next;
//	sub_d_head = NULL;
//	sub_d_last = NULL;
//	while (walk)
//	{
//		if (S_ISDIR(walk->mode))
//			sub_d_last = new_dir(sub_d_last, walk, dir, &sub_d_head);
//		walk = walk->next;
//	}
//	dir->sub_d = sub_d_head;
//	return (sub_d_head);
//}
//
//t_dir	*open_catalog(t_dir *walk)
//{
//	t_dir *sub_u;
//
//	if (walk)
//	{
//		sub_u = walk->sub_u->next;
//		while (walk)
//		{
//			if ((walk->stream = opendir(walk->info->path)) ? (0) : !open_error(&walk))
//				walk = walk->next;
//			else
//				break ;
//		}
//		if (!walk)
//		{
//			walk = open_catalog(sub_u);
//		}
//	}
//	return (walk);
//}
//
//t_dir	*sub_up(t_dir	*dir)
//{
//	if (dir)
//	{
//		if (dir->next)
//			dir = open_catalog(dir->next);
//		else
//			dir = sub_up(dir->sub_u);
//	}
//	return (dir);
//}
//
//void	recursive_help(t_dir **walk, t_dir **save, t_dir **next)
//{
//	closedir((*walk)->stream);
//	(*walk)->stream = NULL;
//	*next = (*walk)->next;
//	*save = (*walk)->sub_u;
//	*walk = check_dir(*walk);
//	if (!(*walk))
//	{
//		*walk = *next;
//		if (!(*walk))
//			*walk = sub_up(*save);
//		else
//			*walk = open_catalog(*walk);
//	}
//	else
//		*walk = open_catalog(*walk);
//}