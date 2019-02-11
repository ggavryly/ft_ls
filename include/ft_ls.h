/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:23:34 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/05 17:23:36 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/include/libft.h"
# include <sys/types.h>
# include <sys/xattr.h>
# include <uuid/uuid.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

# define L	1
# define RR	2
# define A	4
# define R	8
# define T	16

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;
typedef struct			s_info
{
	char				name[256];
	mode_t				mode;
	nlink_t				s_nlink;
	uid_t				s_uid;
	gid_t				st_gid;
	dev_t				st_rdev;
	time_t				time;
	long				ntime;
	off_t				size;
	char				path[1024];
	struct s_info		*next;
}						t_info;
typedef struct			s_dir
{
	DIR					*stream;
	t_info				*info;
	struct s_dir 		*next;
}						t_dir;


int		ft_printf(const char *format, ...);

t_dir	*allocate_mem(t_dir *dir);
t_info	*sort_file_by_ascii(t_info *dir);

int		init_option(int ar, char **av, int	*flags);
t_dir	*init_info(int flags, t_dir *head);
void	display(void);
void	display_default(t_dir *head);

void	path_manage(t_dir *head, char **av, int ar);

void	error_procesing(void);
#endif