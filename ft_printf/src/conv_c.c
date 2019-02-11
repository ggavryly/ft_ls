/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 09:36:13 by ggavryly          #+#    #+#             */
/*   Updated: 2018/12/20 09:36:15 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	field(t_type *con)
{
	int field;

	field = con->field_width;
	if (field > 1)
	{
		field -= 1;
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
}

int			print_c(t_type *con)
{
	char	c;

	c = (char)va_arg(con->ap, int);
	if (con->right_ali)
		field(con);
	ft_putchar(c);
	if (con->left_ali)
		field(con);
	return (++con->print);
}

int			print_perc(t_type *con)
{
	if (con->right_ali)
		field(con);
	ft_putchar('%');
	if (con->left_ali)
		field(con);
	return (++con->print);
}
