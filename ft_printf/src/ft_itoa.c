/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:46:44 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/30 15:41:31 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	swap_sign(intmax_t value, int *sign, char sig)
{
	uintmax_t res;

	if (value < 0)
	{
		if (sig == '1')
			*sign = 1;
		res = -value;
	}
	else
		res = value;
	return (res);
}

static	int			numbers(uintmax_t value)
{
	int i;

	i = 0;
	while (value >= 10)
	{
		value /= 10;
		i++;
	}
	return (i);
}

char				*ft_itoa(intmax_t value, char sig)
{
	int			i;
	char		*str;
	uintmax_t	tmp;
	int			sign;

	i = 0;
	sign = 0;
	tmp = swap_sign(value, &sign, sig);
	i = numbers(tmp);
	if (!(str = (char *)malloc(sizeof(char) * (i + 1 + sign))))
		return (NULL);
	str[i + 1 + sign] = '\0';
	if (sign)
		str[0] = '-';
	while (i >= 0)
	{
		value = tmp % 10;
		str[i + sign] = value + '0';
		tmp /= 10;
		i--;
	}
	return (str);
}
