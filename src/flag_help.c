/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 02:02:54 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/16 02:02:55 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void		total_put(t_info *dir)
{
	intmax_t	block;
	t_info		*walk;

	block = 0;
	if (dir)
	{
		walk = dir->next;
		while (walk)
		{
			block += walk->blocks;
			walk = walk->next;
		}
		ft_printf("total %jd\n", block);
	}
}

static char	file_type(int mode)
{
	mode = (mode & S_IFMT);
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return ('-');
}

static char	list_xattr(char *path)
{
	char	buf[256];

	if (listxattr(path, buf, 256, XATTR_NOFOLLOW) > 0)
		return ('@');
	return (' ');
}

int			flag_l_chmod(t_info *dir)
{
	char	chmod[13];

	chmod[0] = file_type(dir->mode);
	chmod[1] = ((S_IRUSR & dir->mode) ? ('r') : ('-'));
	chmod[2] = ((S_IWUSR & dir->mode) ? ('w') : ('-'));
	chmod[3] = ((S_IXUSR & dir->mode) ? ('x') : ('-'));
	chmod[4] = ((S_IRGRP & dir->mode) ? ('r') : ('-'));
	chmod[5] = ((S_IWGRP & dir->mode) ? ('w') : ('-'));
	chmod[6] = ((S_IXGRP & dir->mode) ? ('x') : ('-'));
	chmod[7] = ((S_IROTH & dir->mode) ? ('r') : ('-'));
	chmod[8] = ((S_IWOTH & dir->mode) ? ('w') : ('-'));
	chmod[9] = ((S_IXOTH & dir->mode) ? ('x') : ('-'));
	chmod[10] = list_xattr(dir->path);
	chmod[11] = '\0';
	if (S_ISUID & dir->mode)
		chmod[3] = chmod[3] == '-' ? 'S' : 's';
	if (S_ISGID & dir->mode)
		chmod[6] = chmod[6] == '-' ? 'S' : 's';
	if (S_ISVTX & dir->mode)
		chmod[9] = chmod[9] == '-' ? 'T' : 't';
	ft_putstr(chmod);
	if (chmod[0] == 'l')
		return (2);
	return (((chmod[0] == 'c' || chmod[0] == 'b') ? (1) : (0)));
}

void		init_recursive_help(t_dir **h, t_dir **l, t_info **t, t_dir **dir)
{
	*h = *dir;
	*t = allocate_info(*t);
	*l = *h;
	(*dir)->stream = opendir((*dir)->info->path);
}

void		close_recursive_help(t_dir **d, t_dir **h)
{
	(*d)->stream ? closedir((*d)->stream) : 1;
	(*d)->stream = NULL;
	while (!(*d)->stream && (*h)->stream)
		*d = (*d)->prev;
}

void		init_data(t_info **tmp_info, t_dire *tmp_dire, t_info **dir)
{
	add_path(*tmp_info, tmp_dire, *dir);
	init_stat(*tmp_info, tmp_dire);
}

int		scip_dot(t_dire *tmp_dire, int flags)
{
	if (tmp_dire->d_name[0] == '.')
	{
		if (flags & A)
			return (0);
		return (1);
	}
	return (0);
}