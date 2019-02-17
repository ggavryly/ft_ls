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

t_info	*sort_file_by_ascii(t_info *info)
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

t_info	*sort_file_by_time(t_info *info)
{
	t_info *head = NULL;
	t_info *tmp = NULL;
	t_info *curr = NULL;

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

t_info *reverse_list(t_info *info)
{
	t_info	*head;
	t_info	*curr;
	t_info	*prev;
	t_info	*next;

	head = info;
	curr = head;
	prev = NULL;
	while(curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head = prev;
	return (head);
}
