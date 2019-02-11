/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 13:08:59 by ggavryly          #+#    #+#             */
/*   Updated: 2019/01/10 13:09:01 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	zero_pad(int field, t_type *con)
{
	if (field >= 0 && !con->precision)
	{
		con->print += field;
		while (field-- > 0)
			write(1, "0", 1);
	}
	else if (field >= 0)
	{
		con->print += field;
		while (field-- > 0)
			write(1, " ", 1);
	}
}

static int	precision(uintmax_t k, t_type *con, int strlen)
{
	int print;
	int prec;

	print = strlen;
	prec = con->precision;
	if (print <= prec)
	{
		prec -= print;
		con->print += prec + strlen;
		while (prec-- > 0)
			write(1, "0", 1);
	}
	else if (prec == -1 && k == 0)
		return (-1);
	else if (prec == 0 || prec < print)
		con->print += print;
	return (1);
}

static void	field(t_type *con, int strlen, char *str)
{
	int prec;
	int field;
	int print;

	prec = con->precision;
	print = (str[0] == '0' && prec == -1) ? 0 : strlen;
	field = con->field_width;
	if (prec > strlen)
		print += prec - strlen;
	else if (prec < strlen && prec > 0)
		print = strlen;
	field -= print;
	if (con->zero_pad && !con->left_ali)
		zero_pad(field, con);
	else if (field >= 0)
	{
		con->print += field;
		while (field-- > 0)
			write(1, " ", 1);
	}
}

int			print_u(t_type *con)
{
	uintmax_t	k;
	int			strlen;
	char		*str;

	k = flag_intoux(con);
	str = itoa_base_u(k, 10, 'a');
	strlen = ft_strlen(str);
	if (con->right_ali)
	{
		if (con->field_width)
			field(con, strlen, str);
	}
	else
		con->zero_pad = 0;
	if (con->precision || strlen)
		if (precision(k, con, strlen) != -1)
			ft_putstr(str);
	if (con->left_ali)
		if (con->field_width)
			field(con, strlen, str);
	free(str);
	return (con->print);
}
