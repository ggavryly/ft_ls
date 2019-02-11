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

static void		init_default(t_dir *dir)
{
	t_info		*curr;
	t_info		*prev;
	t_dirent	*tmp_dirent;
	DIR			*tmp_stream;

	prev = NULL;
	(tmp_stream = opendir(dir->info->path)) ? 0 : error_procesing();
	while ((tmp_dirent = readdir(tmp_stream)))
	{
		if (tmp_dirent->d_name[0] == '.')
			continue;
		curr = (t_info *)malloc(sizeof(t_info));
		ft_strcpy(curr->name, tmp_dirent->d_name);
		if (prev)
			prev->next = curr;
		else if (!prev)
			dir->info->next = curr;
		prev = curr;
		curr->next = NULL;
	}
}

t_dir			*init_info(int flags, t_dir *dir)
{
	init_default(dir);
	return (dir);
}