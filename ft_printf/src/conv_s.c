/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 09:36:21 by ggavryly          #+#    #+#             */
/*   Updated: 2018/12/20 09:36:23 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	field_put(t_type *con, int field, int print)
{
	field -= print;
	con->print += field;
	if (con->zero_pad && !con->left_ali)
	{
		while (field-- > 0)
			write(1, "0", 1);
	}
	else
		while (field-- > 0)
			write(1, " ", 1);
}

static void	field(t_type *con, int strlen)
{
	int field;
	int print;

	print = 0;
	field = con->field_width;
	if (con->precision > 0)
	{
		if (strlen <= con->precision)
			print = strlen;
		else if (con->precision < strlen)
			print = con->precision;
	}
	else if (con->precision == -1)
		strlen = 0;
	else
		print = strlen;
	if (field > print)
	{
		if (con->zero_pad && !con->left_ali)
			field_put(con, field, print);
		else
			field_put(con, field, print);
	}
}

static void	precision(char *str, t_type *con, int strlen)
{
	int prec;
	int i;

	prec = con->precision;
	i = 0;
	if (prec > 0 && strlen > prec)
	{
		if (prec < strlen)
		{
			while (prec-- > 0)
			{
				con->print++;
				ft_putchar(str[i++]);
			}
		}
	}
	else if (prec == 0 || strlen <= prec)
	{
		con->print += strlen;
		ft_putstr(str);
	}
}

int			print_s(t_type *con)
{
	char	*c;
	int		strlen;

	c = va_arg(con->ap, char*);
	strlen = ft_strlen(c);
	if (!c)
	{
		c = "(null)";
		strlen = 6;
	}
	if (con->left_ali)
		precision(c, con, strlen);
	if (con->left_ali)
		if (con->field_width)
			field(con, strlen);
	if (con->right_ali)
		if (con->field_width)
			field(con, strlen);
	if (con->right_ali)
		precision(c, con, strlen);
	return (con->print);
}
