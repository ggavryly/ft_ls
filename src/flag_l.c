/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 03:54:13 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/16 03:54:14 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char	*time_manage(t_info *info)
{
	char	*ctime_tmp;
	char	*time1;
	time_t	time2;

	time1 = ft_strnew(100);
	ctime_tmp = ctime(&info->mtime.tv_sec);
	time(&time2);
	time2 -= info->mtime.tv_sec;
	if ((info->atime.tv_sec - info->mtime.tv_sec) < 15768000
	&& time2 < 15768000)
	{
		ft_strcpy(time1, ctime_tmp + 4);
		time1[12] = '\0';
	}
	else if (time2 > 15768000)
	{
		ft_strncpy(time1, ctime_tmp + 4, 7);
		ft_strcat(time1, ctime_tmp + 20);
		time1[11] = '\0';
	}
	return (time1);
}

void	flag_l_cbl(t_info *info, int flag)
{
	char	buf[256];

	ft_bzero(buf, 256);
	if (flag == 1)
	{
		ft_printf(" %d", major(info->dev));
		ft_printf(", %d  ", minor(info->dev));
	}
	else if (flag == 2)
	{
		readlink(info->path, buf, 256);
		ft_printf("%s -> %s\n", info->name, buf);
	}
}

void	flag_l(t_info *info)
{
	char	*time;
	int		flag;
	t_pass	*k;
	t_gr	*d;

	if (info)
	{
		flag = flag_l_chmod(info);
		write(1, " ", 1);
		time = time_manage(info);
		k = getpwuid(info->uid);
		d = getgrgid(info->gid);
		ft_printf("%3d %-10s %-10s ", info->nlink, k->pw_name,
				d->gr_name);
		if (flag == 1)
			flag_l_cbl(info, 1);
		else if (flag == 0 || flag == 2)
			ft_printf("%10lld ", info->size);
		ft_printf("%-12s ", time);
		if (flag == 2)
			flag_l_cbl(info, 2);
		else
			ft_putendl(info->name);
		free(time);
	}
}
