/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 22:59:52 by ggavryly          #+#    #+#             */
/*   Updated: 2018/12/26 22:59:54 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		scan_flags(const char *str, int *iter, t_type *con)
{
	int	i;

	i = *iter;
	con->right_ali = 1;
	while (str[i] == '0' || str[i] == '+'
	|| str[i] == '-' || str[i] == '#' || str[i] == ' ')
	{
		if (str[i] == '0')
			con->zero_pad = 1;
		else if (str[i] == '+')
			con->sign = 1;
		else if (str[i] == ' ')
			con->space = 1;
		else if (str[i] == '#')
			con->alt_form = 1;
		else if (str[i] == '-')
		{
			con->left_ali = 1;
			con->right_ali = 0;
		}
		i++;
	}
	*iter = i;
}

void		scan_precision(const char *str, int *iter, t_type *con)
{
	int res;
	int i;

	i = *iter;
	if (str[i] == '.')
	{
		i++;
		res = ft_atoi(str + i);
		if (!res)
			con->precision = -1;
		else
			con->precision = res;
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		*iter = i;
	}
}

void		scan_field(const char *str, int *iter, t_type *con)
{
	int res;
	int i;

	i = *iter;
	res = ft_atoi(str + i);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	*iter = i;
	con->field_width = res;
}

void		scan_change(const char *str, int *iter, t_type *con)
{
	int	i;

	i = *iter;
	if (str[i] == 'h' && str[i + 1] == 'h')
		con->hh = 1;
	else if (str[i] == 'h' && str[i + 1] != 'h')
		con->h = 1;
	else if (str[i] == 'l' && str[i + 1] == 'l')
		con->ll = 1;
	else if (str[i] == 'l' && str[i + 1] != 'l')
		con->l = 1;
	else if (str[i] == 'L')
		con->l32 = 1;
	else if (str[i] == 'j')
		con->j = 1;
	else if (str[i] == 'z')
		con->z = 1;
	while (str[i] == 'h' || str[i] == 'l'
	|| str[i] == 'j' || str[i] == 'z')
		i++;
	*iter = i;
}
