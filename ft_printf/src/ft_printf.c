/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 16:56:03 by ggavryly          #+#    #+#             */
/*   Updated: 2018/12/21 16:56:05 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		flag_up(t_type *con)
{
	if (!con->ll)
		con->l = 1;
	con->h = 0;
	con->hh = 0;
}

int			scan_conv(const char *str, t_type *con, int str_len)
{
	int i;

	i = 1;
	con->conversion = '\0';
	if (str[str_len])
	{
		initialize_type(con, str[str_len]);
		if (!ft_strchr("cCspdDioOuUxX%fFv", con->conversion))
		{
			con->conversion = '\0';
			return (-1);
		}
		scan_flags(str, &i, con);
		scan_field(str, &i, con);
		scan_precision(str, &i, con);
		scan_change(str, &i, con);
		if (con->conversion == 'D' || con->conversion == 'U'
		|| con->conversion == 'O' || con->conversion == 'F')
			flag_up(con);
		return (con->conversion);
	}
	return (0);
}

int			print_conv(char con, t_type *c)
{
	if (con == 'c' || con == 'C')
		return (print_c(c));
	else if (con == 's')
		return (print_s(c));
	else if (con == 'p')
		return (print_p(c));
	else if (con == 'd' || con == 'i' || con == 'D')
		return (print_d(c));
	else if (con == 'o' || con == 'O')
		return (print_o(c));
	else if (con == 'u' || con == 'U')
		return (print_u(c));
	else if (con == 'x' || con == 'X')
		return (print_x(c));
	else if (con == 'f' || con == 'F')
		return (print_f(c));
	else if (con == '%')
		return (print_perc(c));
	else if (con == 'v')
		return (send_color(c));
	return (0);
}

int			con_len(const char *str)
{
	int		i;
	int		res;
	char	*s;

	i = 0;
	res = 1;
	s = " #.-+0hlLjz123456789";
	while (str[i])
	{
		if (ft_strchr(s, str[i]))
		{
			res++;
			i++;
		}
		else
			return (res);
	}
	return (res);
}

int			ft_printf(const char *format, ...)
{
	int		conv_len;
	t_type	con;
	int		i;
	int		print;

	i = 0;
	print = 0;
	va_start(con.ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			conv_len = con_len(format + i + 1);
			print += print_conv(scan_conv(format + i, &con, conv_len), &con);
			i += conv_len + ((con.conversion) ? (1) : (0));
		}
		else
		{
			print++;
			ft_putchar(format[i++]);
		}
	}
	va_end(con.ap);
	return (print);
}
