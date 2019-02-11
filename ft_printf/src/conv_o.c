/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 09:39:43 by ggavryly          #+#    #+#             */
/*   Updated: 2018/12/20 09:39:45 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	hash(t_type *con, uintmax_t *k)
{
	if (con->alt_form && *k != 0)
	{
		con->print++;
		write(1, "0", 1);
	}
	else if (con->precision == -1 && *k == 0 && con->alt_form)
	{
		write(1, "0", 1);
		con->print++;
	}
	con->alt_form = 2;
}

static void	zero_pad(int field, t_type *con, uintmax_t *k)
{
	if (con->alt_form != 2 && con->alt_form && !con->precision)
		hash(con, k);
	if (field >= 0 && !con->precision)
	{
		con->print += field;
		while (field-- > 0)
			write(1, "0", 1);
	}
	else if (field >= 0)
	{
		if (*k == 0 && con->precision == -1 && con->alt_form)
			field--;
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

int			print_o(t_type *con)
{
	uintmax_t	k;
	int			strlen;
	char		*str;

	k = flag_intoux(con);
	str = itoa_base_u(k, 8, 'a');
	strlen = ft_strlen(str);
	if (con->right_ali)
	{
		if (con->field_width)
			field(con, strlen, str, &k);
	}
	else
		con->zero_pad = 0;
	if (con->alt_form != 2 && !(con->precision > strlen) && con->alt_form)
		hash(con, &k);
	if (con->precision || strlen)
		if (precision(k, con, strlen) != -1)
			ft_putstr(str);
	if (con->left_ali)
		if (con->field_width)
			field(con, strlen, str, &k);
	free(str);
	return (con->print);
}
