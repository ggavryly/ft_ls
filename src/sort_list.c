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

#include  "../include/ft_ls.h"

static int 	str_ascii(char *s1, char *s2)
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

static t_dir	*sort_dirs(t_dir *info)
{
	t_dir *tmp = NULL;
	t_dir *curr = NULL;
	t_dir *head = NULL;

	while (info)
	{
		tmp = info;
		info = info->next;
		if (head == NULL || !(str_ascii(tmp->info->path, head->info->path)))
		{
			tmp->next = head;
			head = tmp;
		}
		else
		{
			curr = head;
			while (curr->next && str_ascii(tmp->info->path, curr->next->info->path))
				curr = curr->next;
			tmp->next = curr->next;
			curr->next = tmp;
		}
	}
	return (head);
}

static t_info	*sort_file_by_ascii(t_info *info)
{
	t_info *head = NULL;
	t_info *tmp = NULL;
	t_info *curr = NULL;

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

t_dir	*sort(t_dir *head)
{
	t_dir *tmp;

	head = sort_dirs(head);
	tmp = head;
	while (tmp)
	{
		tmp->info->next = sort_file_by_ascii(tmp->info->next);
		tmp = tmp->next;
	}
	return (head);
}

void	add_to_list_dir(t_dir *curr, t_dir *prev)
{
	t_dir *last;

	last = NULL;
	while (prev)
	{
		last = prev;
		prev = prev->next;
	}
	if (last)
	{
		last->next = curr;
		curr->prev = last;
	}
}
