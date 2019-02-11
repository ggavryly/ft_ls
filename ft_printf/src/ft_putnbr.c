/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:34:05 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/31 23:23:09 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	init(intmax_t val, int *sign)
{
	uintmax_t res;

	if (val < 0)
	{
		if (*sign)
			*sign = 3;
		res = (uintmax_t)-val;
	}
	else
	{
		if (*sign)
			*sign = 1;
		res = (uintmax_t)val;
	}
	return (res);
}

static	char		*str_mem(uintmax_t res, int *count1, int sign)
{
	char	*str;
	int		count;

	count = 0;
	if (res == 0)
		count++;
	if (sign)
		count++;
	while (res)
	{
		res /= 10;
		count++;
	}
	str = (char *)malloc(count + 1);
	*count1 = count;
	return (str);
}

void				ft_putnbr(intmax_t val, int sign)
{
	uintmax_t	print;
	int			count;
	char		*str;

	count = 0;
	print = init(val, &sign);
	str = str_mem(print, &count, sign);
	str[count--] = '\0';
	while (count >= 0)
	{
		if (print >= 10)
			str[count] = (char)(print % 10 + '0');
		else
			str[count] = (char)(print + '0');
		print /= 10;
		count--;
	}
	if (sign)
		str[0] = 42 + sign;
	ft_putstr(str);
	free(str);
}
