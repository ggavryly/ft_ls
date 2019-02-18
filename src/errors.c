/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 21:05:14 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/07 21:05:16 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	put_error(t_dir *dir)
{
	ft_putstr_fd(dir->info->name, 2);
	ft_putstr_fd("\n", 2);
}

int		open_error(t_dir **if_error)
{
	char str[256];

	(*if_error)->info->error_num = 1;
	ft_strcpy(str, (*if_error)->info->name);
	ft_strcpy((*if_error)->info->name, "ft_ls: ");
	ft_strcat((*if_error)->info->name, str);
	ft_strcat((*if_error)->info->name, ": ");
	ft_strcat((*if_error)->info->name, strerror(errno));
	return (0);
}

void	put_err(t_info *error, int mode)
{
	if (error->error_num == 2 && mode == 1)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(error->path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(error->error_num), 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error->error_num == 20 && mode == 2)
	{
		ft_putstr(error->path);
		ft_putstr("\n");
	}
}

t_info	*del_error(t_info *del_me, t_info *prev, int mode, int *flag)
{
	if (del_me->error_num == 2 && mode == 1)
	{
		prev->next = del_me->next;
		free(del_me);
	}
	else if (del_me->error_num == 20 && mode == 2)
	{
		*flag = 1;
		prev->next = del_me->next;
		free(del_me);
	}
	else
		return (del_me);
	return (prev);
}

t_info	*error_check(t_info *args, int mode)
{
	t_info	*prev;
	t_info	*walk;
	int		flag;

	flag = 0;
	prev = NULL;
	walk = args;
	while (walk)
	{
		if (walk->error_num)
		{
			put_err(walk, mode);
			walk = del_error(walk, prev, mode, &flag);
		}
		prev = walk;
		walk = walk->next;
	}
	if (flag)
		write(1, "\n", 1);
	return (args);
}
