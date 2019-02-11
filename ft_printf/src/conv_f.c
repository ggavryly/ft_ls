/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:26:17 by ggavryly          #+#    #+#             */
/*   Updated: 2019/01/14 15:26:18 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	sign(long double *k, t_type *con)
{
	if (((con->sign) || *k < 0.0 || con->space))
	{
		if (*k < 0.0)
			write(1, "-", 1);
		else if (con->sign)
			write(1, "+", 1);
		else if (con->space)
			write(1, " ", 1);
		if (!con->left_ali)
		{
			con->sign = 0;
			*k = 0.0;
			con->space = 0;
		}
		con->print++;
	}
}

static void	zero_pad(int field, t_type *con, long double *k)
{
	if (con->sign || con->space || *k < 0.0)
		sign(k, con);
	if (field >= 0)
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

static void	field(long double *k, int len, t_type *con)
{
	int field;
	int print;

	print = len;
	field = con->field_width;
	if (con->sign || *k < 0.0 || con->space)
		print += 1;
	field -= print;
	if (con->zero_pad && !con->left_ali)
		zero_pad(field, con, k);
	else if (field >= 0)
	{
		con->print += field;
		while (field-- > 0)
			write(1, " ", 1);
	}
}

int			print_f(t_type *con)
{
	long double	k;
	int			len;
	char		*buf;

	k = flag_float(con);
	k = float_up(k, (con->precision ? con->precision : 6));
	buf = float_str(((k < 0.0) ? (-k) : (k)), con);
	len = ft_strlen(buf);
	if (con->right_ali)
	{
		if (con->field_width)
			field(&k, len, con);
	}
	else
		con->zero_pad = 0;
	if (con->sign || k < 0 || con->space)
		sign(&k, con);
	ft_putstr(buf);
	con->print += len;
	if (con->left_ali)
		if (con->field_width)
			field(&k, len, con);
	free(buf);
	return (con->print);
}
