/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:04:21 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/07 15:04:23 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static	void	split_option(int i, char **av, int *flags)
{
	int j;

	j = 0;
	while (av[i][j])
	{
		(av[i][j] == 'l') ? *flags |= L : 0;
		(av[i][j] == 'R') ? *flags |= RR : 0;
		(av[i][j] == 'a') ? *flags |= A : 0;
		(av[i][j] == 'r') ? *flags |= R : 0;
		(av[i][j] == 't') ? *flags |= T : 0;
		j++;
	}
}

int		init_option(int ar, char **av, int *flags)
{
	int i;

	i = 1;
	while (i < ar && av[i][0] == '-' && av[i][1])
	{
		(av[i][1] == 'l') ? *flags |= L : 0;
		(av[i][1] == 'R') ? *flags |= RR : 0;
		(av[i][1] == 'a') ? *flags |= A : 0;
		(av[i][1] == 'r') ? *flags |= R : 0;
		(av[i][1] == 't') ? *flags |= T : 0;
		if (av[i][2])
			split_option(i, av, flags);
		i++;
	}
	return (i - 1);
}
