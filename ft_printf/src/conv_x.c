/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 09:39:51 by ggavryly          #+#    #+#             */
/*   Updated: 2018/12/20 09:40:06 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hash(t_type *con, uintmax_t *k)
{
	if (con->alt_form && *k != 0)
	{
		if (con->conversion == 'x')
			write(1, "0x", 2);
		else if (con->conversion == 'X')
			write(1, "0X", 2);
		con->print += 2;
		*k = 0;
	}
	return (1);
}

static void	zero_pad(int field, t_type *con, uintmax_t *k)
{
	if (con->alt_form && !con->precision)
		hash(con, k);
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

static int	precision(char *str, t_type *con, int strlen)
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
	else if (prec == -1 && str[0] == '0')
		return (-1);
	else if (prec == 0 || prec < print)
		con->print += print;
	return (1);
}

static void	field(t_type *con, int strlen, char *str, uintmax_t *k)
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
	if (con->alt_form && str[0] != '0')
		print += 2;
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

int			print_x(t_type *con)
{
	uintmax_t	k;
	int			strlen;
	char		*str;

	k = flag_intoux(con);
	str = itoa_base(k, 16, ((con->conversion == 'x') ? 'a' : 'A'));
	strlen = ft_strlen(str);
	if (con->right_ali)
	{
		if (con->field_width)
			field(con, strlen, str, &k);
	}
	else
		con->zero_pad = 0;
	if (con->alt_form)
		hash(con, &k);
	if (con->precision || strlen)
		if (precision(str, con, strlen) != -1)
			ft_putstr(str);
	if (con->left_ali)
		if (con->field_width)
			field(con, strlen, str, &k);
	free(str);
	return (con->print);
}
