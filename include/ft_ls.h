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

typedef struct stat		t_st;
typedef struct dirent	t_dire;
typedef struct			s_info
{
	char				name[256];
	mode_t				mode;
	nlink_t				nlink;
	uid_t				uid;
	gid_t				gid;
	dev_t				dev;
	struct timespec		atime;
	struct timespec		mtime;
	struct timespec		ctime;
	off_t				size;
	char				path[1024];
	struct s_info		*next;
}						t_info;
typedef struct			s_dir
{
	DIR					*stream;
	t_info				*info;
	struct s_dir 		*next;
	struct s_dir		*prev;
}						t_dir;


int		ft_printf(const char *format, ...);

t_dir	*allocate_dir(t_dir *dir);
t_info	*allocate_info(t_info *info);
t_info	*sort_file_by_ascii(t_info *dir);
t_dir	*new_dir(t_dir *curr, t_info *tmp_info, t_dir *dir);
t_info	*new_node(t_info *info, t_info *tmp_info);
void	list_free(t_dir *dir);

int		init_option(int ar, char **av, int	*flags);
t_dir	*init_info(int flags, t_dir *head);
void	display(void);
void	display_default(t_dir *head);
t_dir	*display_dirs(t_dir *head);
void	info_copy(t_info *dst, t_info *tmp_info);

void	path_manage(t_dir *head, char **av, int ar);
void	add_path(t_info *curr, t_dire *curr_dire, t_info *list);

void	error_procesing(void);
#endif