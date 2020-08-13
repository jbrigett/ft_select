/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 18:31:04 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/08 17:36:49 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <ctype.h>
# include <limits.h>
# include "libft.h"

# define PLUS			(1 << 0)
# define MINUS			(1 << 1)
# define SHARP			(1 << 2)
# define ZERO			(1 << 3)
# define SPACE			(1 << 4)
# define PTRDIFF		(1 << 5)

# define SHORT			(1 << 6)
# define SSHORT			(1 << 7)
# define LONG			(1 << 8)
# define LLONG			(1 << 9)
# define UPPER			(1 << 10)
# define INTMAX			(1 << 11)
# define SIZE_T			(1 << 12)
# define LDOUBLE		(1 << 13)
# define PRECISION		(1 << 14)
# define POINTER		(1 << 15)

# define LD_MASK 		0xFFF
# define LD_CHECK		0x7FF

# define LD_FRAC		0x000FFFFFFFFFFFFF
# define LD_MASK_LONG 	0x7FFFFFFFFFFFFFFF

typedef struct	s_format
{
	const char	*str;
	uint32_t	fl;
	int			fd;
	int32_t		len;
	int32_t		width;
	int32_t		prec;
	int32_t		base;
	int32_t		to_print;
	char		spec;
	char		*pref;
	va_list		ap;
}				t_format;

typedef struct	s_double
{
	uint64_t	integer;
	int64_t		exp;
	long double	fraction;
	long double	n;
	int			sign;
}				t_double;

/*
** main function
*/
int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);

/*
** print CS NOT FOUND
*/
void			cs_not_found(t_format *frmt);
void			print_n(t_format *format);

/*
** Parsing each argument's format string
*/
void			parser(char **str, t_format *frmt);
int32_t			flag_parser(char **str, t_format *frmt);
int32_t			width_parser(char **str, t_format *frmt);
int32_t			precision_parser(char **str, t_format *frmt);
int32_t			length_parser(char **str, t_format *frmt);
int32_t			spec_parser(char **str, t_format *frmt);
void			base_parser(t_format *frmt);
int32_t			mode_parser(t_format *frmt);
void			set_upper_flag(char c, t_format *format);

/*
** ITOA W/ BASE
*/
void			itoa_base(t_format *frmt, uintmax_t n, char *str);
void			print_itoa_base(uintmax_t n, t_format *frmt);

/*
** printing with spec D, I
*/
void			print_di(t_format *frmt);
void			add_sign(intmax_t n, t_format *frmt, char *str);
void			set_width(intmax_t n, t_format *frmt);
void			settings_d(intmax_t n, t_format *frmt);

/*
** printhing spec B, X, O, U
*/
void			print_bxou(t_format *frmt);
void			settings_bxou(uintmax_t n, t_format *frmt);
void			set_width_base(t_format *frmt, uintmax_t n);
void			print_prefix(uintmax_t n, t_format *frmt);

/*
** prining floats: A, F, G, E
*/
void			print_aefg(t_format *frmt);

/*
** print F
*/
void			print_f(t_format *frmt, long double d);
int				check_spec_val(t_format *frmt, long double n);
void			print_sign(t_double *d, t_format *frmt);
void			print_fraction(t_double *t, t_format *frmt);
void			set_parts(t_format *frmt, t_double *t);
void			help_nan(t_format *frmt, uint64_t integ);
void			help_inf(t_format *frmt, uint64_t integ);

/*
** print A, E
*/
void			print_ae(t_format *frmt, long double d);
void			set_exp(t_double *doub, t_format *frmt);
void			print_exp(int64_t exp, t_format *frmt);
void			set_width_ae(t_double *d, t_format *frmt);

/*
** print G
*/
void			print_g(t_format *frmt, long double d);
int32_t			compare_fe(long double d, t_format *frmt);

/*
** print C and lC
*/
void			print_c(t_format *frmt);
void			print_wchar(wint_t c, t_format *frmt);
void			oct_2(wint_t c, t_format *frmt);
void			oct_3(wint_t c, t_format *frmt);
void			oct_4(wint_t c, t_format *frmt);

/*
** print S
*/
void			print_s(t_format *frmt);

/*
** print WS
*/
void			print_ws(t_format *frmt);
size_t			ft_wcharlen(wint_t c);
void			print_wstring(wchar_t *wstr, t_format *frmt, int64_t strlen);
int64_t			wslen(wchar_t *wstr, t_format *frmt);

/*
** print P
*/
void			print_p(t_format *frmt);

/*
** print %
*/
void			print_percent(t_format *frmt);

/*
** print all
*/
void			print_all(t_format *frmt, char *str, int len);
void			padding(t_format *frmt, char c, int len);

/*
** HELP FOR WSTRING
*/
void			print_null(t_format *frmt);
wchar_t			*wstrdup(wchar_t *str);
wchar_t			*wstrndup(wchar_t *s1, size_t n);
char			*ft_strndup(const char *s1, size_t n);

/*
** HELP FUNCTIONS FOR FLOAT
*/
long double		ft_fabsl(long double d);
intmax_t		ft_roundl(long double d, int32_t prec);
uintmax_t		ft_imaxabs(intmax_t n);

/*
** HELP FUNCTIONS
*/
void			init_format(int fd, t_format *format, const char *str);
void			reinit_format(t_format *format);
int8_t			ft_isupper(char c);
intmax_t		ft_max(intmax_t a, intmax_t b);
size_t			length_base(uintmax_t n, int8_t base);
int				ft_strchr_index(const char *s, int c);

#endif
