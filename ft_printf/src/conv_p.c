/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 09:36:27 by ggavryly          #+#    #+#             */
/*   Updated: 2018/12/20 09:36:29 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	field(t_type *con, int strlen)
{
	int print;
	int prec;
	int field;

	print = strlen + 2;
	field = con->field_width;
	prec = con->precision;
	if (prec > print)
		print = prec;
	if (field > print)
	{
		field -= print;
		con->print += field;
		while (field-- > 0)
			ft_putchar(' ');
	}
}

static void	precision(t_type *con, int strlen, char *str)
{
	int prec;

	prec = con->precision;
	con->print += 2;
	if (prec > strlen)
	{
		prec -= strlen;
		con->print += prec;
		con->print += strlen;
		while (prec-- > 0)
			ft_putchar('0');
		ft_putstr(str);
	}
	else if (prec != -1)
	{
		con->print += strlen;
		ft_putstr(str);
	}
}

int			print_p(t_type *con)
{
	uintmax_t	k;
	char		*str;
	int			strlen;

	k = (uintmax_t)va_arg(con->ap, void*);
	str = itoa_base_u(k, 16, 'a');
	strlen = (((k == 0 && con->precision == -1) ? (0) : (ft_strlen(str))));
	if (con->right_ali)
		if (con->field_width)
			field(con, strlen);
	ft_putstr("0x");
	if (con->precision)
		precision(con, strlen, str);
	else
	{
		con->print += 2;
		con->print += strlen;
		ft_putstr(str);
	}
	if (con->left_ali)
		if (con->field_width)
			field(con, strlen);
	free(str);
	return (con->print);
}
