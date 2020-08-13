/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:52:41 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/21 15:05:35 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int32_t	flag_parser(char **str, t_format *frmt)
{
	int n;

	if (ft_strchr_index("+-#0 ", **str) == -1)
		return (0);
	while ((n = ft_strchr_index("+-#0 ", **str)) >= 0 && ++(*str))
		frmt->fl |= (1 << n);
	(frmt->fl & PLUS) ? frmt->fl &= ~SPACE : 0;
	(frmt->fl & MINUS) ? frmt->fl &= ~ZERO : 0;
	return (1);
}

int32_t	width_parser(char **str, t_format *frmt)
{
	int n;

	if (**str == '*')
	{
		n = (int)va_arg(frmt->ap, int);
		(n < 0) ? (frmt->fl |= MINUS) : 0;
		(frmt->fl & MINUS) ? frmt->fl &= ~ZERO : 0;
		n = (n < 0) ? -n : n;
		frmt->width = n;
		++(*str);
		return (1);
	}
	else if ((n = ft_max(ft_atoi(*str), 0)))
	{
		if (ft_isdigit(**str))
			frmt->width = n;
		while (ft_isdigit(**str))
			++(*str);
		return (1);
	}
	return (0);
}

int32_t	precision_parser(char **str, t_format *frmt)
{
	if (**str != '.')
		return (0);
	frmt->fl |= PRECISION;
	++(*str);
	if (**str == '*')
	{
		if ((frmt->prec = (int)va_arg(frmt->ap, int)) < 0)
		{
			frmt->fl &= ~PRECISION;
			frmt->prec = 1;
		}
		++(*str);
	}
	else
	{
		frmt->prec = ft_max(ft_atoi(*str), 0);
		while (ft_isdigit(**str))
			++(*str);
	}
	return (1);
}

int32_t	length_parser(char **str, t_format *frmt)
{
	if (!(ft_memchr("hljzL", **str, 5)))
		return (0);
	if (**str == 'h')
		frmt->fl |= (*(*str + 1) == 'h') ? SSHORT : SHORT;
	else if (**str == 'l')
		frmt->fl |= (*(*str + 1) == 'l') ? LLONG : LONG;
	else if (**str == 'j')
		frmt->fl |= INTMAX;
	else if (**str == 'z')
		frmt->fl |= SIZE_T;
	else if (**str == 'L')
		frmt->fl |= LDOUBLE;
	++(*str);
	if (frmt->fl & LLONG && (**str == 'l'))
		++(*str);
	if (frmt->fl & SSHORT && (**str == 'h'))
		++(*str);
	return (1);
}

void	parser(char **str, t_format *frmt)
{
	++(*str);
	if (!**str)
		return ;
	reinit_format(frmt);
	while (21)
	{
		if (flag_parser(str, frmt) == 1)
			continue ;
		if (width_parser(str, frmt) == 1)
			continue ;
		if (precision_parser(str, frmt) == 1)
			continue ;
		if (length_parser(str, frmt) == 1)
			continue ;
		if (spec_parser(str, frmt) == 0)
			continue ;
		else
			break ;
	}
}
