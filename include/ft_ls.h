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
# include <sys/acl.h>
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
# define BIG 32

typedef struct stat		t_st;
typedef struct group	t_gr;
typedef struct passwd	t_pass;
typedef struct dirent	t_dire;

typedef struct		s_info
{
	int				error_num;
	char			name[256];
	mode_t			mode;
	nlink_t			nlink;
	uid_t			uid;
	gid_t			gid;
	dev_t			dev;
	struct timespec	atime;
	struct timespec	mtime;
	struct timespec	ctime;
	off_t			size;
	blkcnt_t		blocks;
	char			path[1024];
	struct s_info	*next;
}					t_info;

typedef struct		s_dir
{
	DIR				*stream;
	t_info			*info;
	struct s_dir	*sub_d;
	struct s_dir	*next;
	struct s_dir	*sub_u;
}					t_dir;

int					ft_printf(const char *format, ...);

t_dir				*allocate_dir(t_dir *dir);
t_info				*allocate_info(t_info *info);
int					str_ascii(const char *s1, const char *s2);

t_dir	*new_dir(t_dir *sub_d, t_info *dir_info, t_dir *sub_u, t_dir **head);
void				new_node(t_dir *i, t_info *t_i);
t_info				*sort_file_by_ascii(t_info *info);
t_info				*sort_file_by_time(t_info *info);
t_dir				*sort_dirs_by_ascii(t_dir *info);
t_dir				*sort(t_dir	*dir, int flags);
t_dir				*reverse_dir(t_dir *info);
t_info				*reverse_info(t_info *info);
void				free_path(char **path_ar);

int					init_option(int ar, char **av, int	*flags);
t_dir				*init_info(int flags, t_dir *head);
t_dir				*display(t_dir *dir, int flags);
void				info_copy(t_info *dst, t_info *tmp_info);

void				path_manage(t_dir *curr, t_info *curr_ar_path);
void				add_path(t_info *curr, t_dire *curr_dire, t_info *list);
t_info				*init_start(int ar, char **av, int *flags, t_info *args);
void				put_err(t_info *error, int mode);
t_info				*error_check(t_info *args, int mode);

int					open_error(t_dir **if_error);
void				put_error(t_dir *dir);

void				total_put(t_info *info);
void				flag_l(t_info *info);
int					flag_l_chmod(t_info *dir);
void				init_stat(t_info *tmp_inf, t_dire *tmp_dire);

void				recursive(t_dir **h, t_dir **l, t_info **t, t_dir **d);
void				close_recursive_help(t_dir **d, t_dir **h);
void				init_data(t_info **tl, t_dire *t, t_info **d);
int					scip_dot(t_dire *tmp_dire, int flags);

#endif
