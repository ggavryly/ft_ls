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
}

int		open_error(t_dir **if_error)
{
	char str[256];

	(*if_error)->info->error = 1;
	ft_strcpy(str,(*if_error)->info->name);
	ft_strcpy((*if_error)->info->name, "ft_ls: ");
	ft_strcat((*if_error)->info->name, str);
	ft_strcat((*if_error)->info->name, ": ");
	ft_strcat((*if_error)->info->name, strerror(errno));
	return (0);
}

//int		open_start(char **av)
//{
//	t_err *new;
//	t_err *tmp;
//
//	new = NULL;
//	new = allocate_err(new);
//	ft_strcpy(new->err_message, "ft_ls: ");
//	ft_strcat(new->err_message, (*if_error)->info->name);
//	ft_strcat(new->err_message, ": ");
//	ft_strcat(new->err_message, strerror(errno));
//	free((*if_error)->info);
//	free(*if_error);
//	(*if_error) = NULL;
//	while (*err_head)
//	{
//		tmp = (*err_head);
//		(*err_head) = (*err_head)->next;
//	}
//	tmp->next = new;
//	return (0);
//}