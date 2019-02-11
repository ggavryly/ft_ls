/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 20:47:19 by ggavryly          #+#    #+#             */
/*   Updated: 2019/01/19 20:47:26 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	flag_intdi(t_type *con)
{
	intmax_t k;

	if (con->hh)
		k = (char)va_arg(con->ap, int);
	else if (con->h)
		k = (short)va_arg(con->ap, int);
	else if (con->l)
		k = va_arg(con->ap, long);
	else if (con->ll)
		k = va_arg(con->ap, long long);
	else if (con->j)
		k = va_arg(con->ap, intmax_t);
	else if (con->z)
		k = va_arg(con->ap, ssize_t);
	else
		k = va_arg(con->ap, int);
	return (k);
}

intmax_t	flag_intoux(t_type *con)
{
	uintmax_t	k;

	if (con->hh)
		k = (unsigned char)va_arg(con->ap, unsigned int);
	else if (con->h)
		k = (unsigned short)va_arg(con->ap, unsigned int);
	else if (con->l)
		k = va_arg(con->ap, unsigned long);
	else if (con->ll)
		k = va_arg(con->ap, unsigned long long);
	else if (con->j)
		k = va_arg(con->ap, uintmax_t);
	else if (con->z)
		k = (uintmax_t)va_arg(con->ap, size_t);
	else
		k = va_arg(con->ap, unsigned int);
	return (k);
}

long double	flag_float(t_type *con)
{
	long double k;

	if (con->l32)
		k = va_arg(con->ap, long double);
	else if (con->l)
		k = (long double)va_arg(con->ap, double);
	else
		k = (long double)va_arg(con->ap, double);
	return (k);
}

long double	float_up(long double nbr, int precision)
{
	long double		f;
	int				n;

	if (precision >= 0)
	{
		f = 0.5;
		n = 0;
		while (n++ < precision)
			f /= 10;
		if (nbr > 0)
			nbr += f;
		else if (nbr < 0)
			nbr -= f;
	}
	else
	{
		if (nbr < 0)
			nbr -= 0.0000005;
		else if (nbr > 0)
			nbr += 0.0000005;
	}
	return (nbr);
}

int			send_color(t_type *con)
{
	char	*color;

	color = va_arg(con->ap, char *);
	if (!ft_strcmp(color, RED) ||
		!ft_strcmp(color, BLACK) ||
		!ft_strcmp(color, BLUE) ||
		!ft_strcmp(color, GREEN) ||
		!ft_strcmp(color, YELLOW) ||
		!ft_strcmp(color, PURPLE) ||
		!ft_strcmp(color, CYAN) ||
		!ft_strcmp(color, END_COLOR))
		ft_putstr(color);
	return (0);
}
