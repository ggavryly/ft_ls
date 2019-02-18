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

int				init_option(int ar, char **av, int *flags)
{
	int i;

	i = 1;
	while (i < ar && av[i][0] == '-' && av[i][1])
	{
		if (av[i][1] != 'l' && av[i][1] != 'R' && av[i][1] != 'a'
		&& av[i][1] != 'r' && av[i][1] != 't')
		{
			ft_putstr("ft_ls: illegal option : -- ");
			ft_putchar(av[i][1]);
			ft_putstr("\nusage: ft_ls [-lRart] [file ...]\n");
			exit(0);
		}
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

char			**init_args(char **av, int ar)
{
	char	**str_ar;
	int		i;

	i = 0;
	if (ar)
	{
		str_ar = (char **)malloc((sizeof(char *) * ar + 1));
		str_ar[ar] = NULL;
		while (*av)
		{
			str_ar[i] = (char *)malloc((sizeof(char) * ft_strlen(*av) + 1));
			str_ar[i][ft_strlen(*av)] = '\0';
			ft_strcpy(str_ar[i++], *av++);
		}
	}
	else
	{
		str_ar = (char **)malloc((sizeof(char *) * 2));
		str_ar[0] = (char *)malloc(sizeof(char) * 2);
		ft_strcpy(str_ar[0], ".");
		str_ar[1] = NULL;
	}
	return (str_ar);
}

t_info			*test_args(t_info *args, char **path_ar)
{
	t_info		*curr;
	t_info		*prev;
	DIR			*tmp_stream;

	prev = NULL;
	curr = NULL;
	args = allocate_info(args);
	args->error_num = 0;
	while (*path_ar)
	{
		curr = allocate_info(curr);
		if (!(tmp_stream = opendir(*path_ar)))
			curr->error_num = errno;
		ft_strcpy(curr->path, *path_ar);
		if (prev)
			prev->next = curr;
		else
			args->next = curr;
		prev = curr;
		path_ar++;
		if (tmp_stream)
			closedir(tmp_stream);
	}
	return (args);
}

t_info			*init_start(int ar, char **av, int *flags, t_info *args)
{
	int		tmp;
	char	**path_ar;

	tmp = init_option(ar, av, flags);
	ar -= tmp + 1;
	av += tmp + 1;
	path_ar = init_args(av, ar);
	args = test_args(args, path_ar);
	args = sort_file_by_ascii(args);
	if (args->next->next)
		(*flags) |= BIG;
	args = error_check(args, 1);
	args = error_check(args, 2);
	free_path(path_ar);
	return (args);
}
