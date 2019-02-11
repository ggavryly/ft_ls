/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 20:27:47 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/07 20:27:48 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

DIR		*new_dir(t_dir *curr)
{
	t_dir *new_dir;

	new_dir = allocate_dir(new_dir);
	(new_dir->stream = opendir(new_dir->info->path)) ? NULL : error_procesing();
	curr->next = new_dir;
	new_dir->prev = curr;
	return (new_dir->stream);
}

void	new_node(t_dir *curr, t_dire *tmp)
{
	t_info	*new;

	allocate_info(new);
	ft_strcpy(new->name, tmp->d_name);
	curr->info->next = new;
}
