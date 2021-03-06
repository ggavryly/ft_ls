/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 18:42:21 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/10 18:42:22 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int			str_ascii(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] < s2[i])
			return (0);
		else if (s1[i] > s2[i])
			return (1);
		i++;
	}
	if (!s1[i] && s2[i])
		return (0);
	else
		return (1);
}

t_info		*sort_file_by_ascii(t_info *info)
{
	t_info	*head;
	t_info	*tmp;
	t_info	*curr;

	head = NULL;
	while (info)
	{
		tmp = info;
		info = info->next;
		if (head == NULL || !(str_ascii(tmp->name, head->name)))
		{
			tmp->next = head;
			head = tmp;
		}
		else
		{
			curr = head;
			while (curr->next && str_ascii(tmp->name, curr->next->name))
				curr = curr->next;
			tmp->next = curr->next;
			curr->next = tmp;
		}
	}
	return (head);
}

t_info		*sort_file_by_time(t_info *info)
{
	t_info *head;
	t_info *tmp;
	t_info *curr;

	head = NULL;
	while (info)
	{
		tmp = info;
		info = info->next;
		if (head == NULL || tmp->mtime.tv_sec > head->mtime.tv_sec)
		{
			tmp->next = head;
			head = tmp;
		}
		else
		{
			curr = head;
			while (curr->next && tmp->mtime.tv_sec <= curr->next->mtime.tv_sec)
				curr = curr->next;
			tmp->next = curr->next;
			curr->next = tmp;
		}
	}
	return (head);
}

t_dir		*sort(t_dir *head, int flags)
{
	t_dir *dir;

	dir = head;
	if (flags & T)
		dir->info->next = sort_file_by_time(dir->info->next);
	else
		dir->info->next = sort_file_by_ascii(dir->info->next);
	if (flags & R)
		dir->info->next = reverse_dir(dir->info->next);
	return (head);
}

void		init_data(t_info **tmp_info, t_dire *tmp_dire, t_info **dir)
{
	add_path(*tmp_info, tmp_dire, *dir);
	init_stat(*tmp_info, tmp_dire);
}
