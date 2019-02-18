/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 20:32:20 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/31 23:26:08 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_delim(char const *s, char d)
{
	unsigned int	k;
	unsigned int	i;

	if (s)
	{
		i = 0;
		k = 0;
		while (s[i])
		{
			while (s[i] && s[i] == d)
				i++;
			if (s[i] && !(s[i] == d))
			{
				while (s[i] && !(s[i] == d))
					i++;
				k++;
			}
		}
		return (k);
	}
	return (0);
}

static unsigned int	ft_strln(const char *s, char d)
{
	unsigned int	i;

	i = 0;
	while (s[i] != d && s[i])
	{
		i++;
	}
	return (i);
}

char				**ft_strsplit(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			**res;

	res = NULL;
	i = 0;
	k = ft_delim(s, c);
	if (s && (res = (char **)malloc(sizeof(char *) * k + 1)))
	{
		res[k] = NULL;
		k = 0;
		while (s[i])
		{
			while (s[i] == c && s[i])
				i++;
			j = ft_strln(s + i, c);
			if (s[i] && (res[k] = ft_strsub(s, i, j)))
				k++;
			while (s[i] != c && s[i])
				i++;
		}
		return (res);
	}
	return (NULL);
}
