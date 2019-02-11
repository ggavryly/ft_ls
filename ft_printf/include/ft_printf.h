/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 11:20:44 by ggavryly          #+#    #+#             */
/*   Updated: 2018/12/20 11:20:55 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>

# define BLACK		"\033[37m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PURPLE		"\033[35m"
# define CYAN		"\033[36m"
# define BLACK		"\033[37m"
# define END_COLOR	"\033[0m"

typedef struct	s_conv
{
	va_list		ap;
	char		conversion;
	int			field_width;
	int			precision;
	int			alt_form;
	int			left_ali;
	int			right_ali;
	int			sign;
	int			space;
	int			zero_pad;
	int			h;
	int			hh;
	int			l;
	int			ll;
	int			l32;
	int			j;
	int			z;
	int			print;
}				t_type;

int				ft_printf(const char *format, ...);

void			ft_putchar(char c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_atoi(const char *str);
char			*ft_itoa(intmax_t value, char sig);
void			ft_putstr(char const *s);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlen(const char *s);
char			*itoa_base(intmax_t value, uintmax_t base, char a_a32);
char			*itoa_base_u(uintmax_t value, uintmax_t base, char a_a32);

int				scan_conv(const char *str, t_type *con, int str_len);
void			scan_precision(const char *str, int *iter, t_type *con);
void			scan_field(const char *str, int *iter, t_type *con);
void			scan_flags(const char *str, int *iter, t_type *con);
void			scan_change(const char *str, int *iter, t_type *con);

int				con_len(const char *str);
void			initialize_type(t_type *con, char conv);
intmax_t		flag_intdi(t_type *con);
intmax_t		flag_intoux(t_type *con);
void			flag_up(t_type *con);
long double		flag_float(t_type *con);
char			*float_str(long double k, t_type *con);
long double		float_up(long double nbr, int precision);
int				send_color(t_type *con);

int				print_conv(char con, t_type *c);
int				print_p(t_type *con);
int				print_s(t_type *con);
int				print_c(t_type *con);
int				print_d(t_type *con);
int				print_x(t_type *con);
int				print_o(t_type *con);
int				print_u(t_type *con);
int				print_f(t_type *con);
int				print_perc(t_type *con);

#endif
