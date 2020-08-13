/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bxou.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:53:33 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/22 18:29:20 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_prefix(uintmax_t n, t_format *frmt)
{
	char	*pref;

	pref = "";
	if (frmt->base == 16)
		pref = (frmt->fl & UPPER) ? "0X" : "0x";
	if (frmt->base == 2)
		pref = (frmt->fl & UPPER) ? "0B" : "0b";
	if (((n != 0) || frmt->fl & POINTER || frmt->base == 8) && frmt->fl & SHARP)
		print_all(frmt, pref, ft_strlen(pref));
}

void	set_width_base(t_format *frmt, uintmax_t n)
{
	uintmax_t	tmp;

	frmt->len = 0;
	tmp = n;
	while (tmp > 0)
	{
		tmp /= frmt->base;
		++frmt->len;
	}
	if (frmt->base == 8 && frmt->fl & SHARP)
		if (frmt->len >= frmt->prec)
			frmt->prec = frmt->len + 1;
	frmt->len = ft_max(frmt->len, frmt->prec);
	if (frmt->base == 8 && frmt->fl & SHARP && !n &&
			frmt->fl & PRECISION && frmt->prec <= 0)
		++frmt->len;
	if (frmt->base != 8 && frmt->fl & SHARP &&
			((n != 0 && frmt->spec != 'p') || frmt->spec == 'p'))
		frmt->width -= 2;
}

void	settings_bxou(uintmax_t n, t_format *frmt)
{
	char	str[21];

	if (frmt->fl & PRECISION)
		frmt->fl &= ~ZERO;
	set_width_base(frmt, n);
	if (!(frmt->fl & MINUS) && !(frmt->fl & ZERO))
		padding(frmt, ' ', frmt->width - frmt->len);
	print_prefix(n, frmt);
	if (!(frmt->fl & MINUS) && frmt->fl & ZERO && !(frmt->fl & PRECISION))
		padding(frmt, '0', frmt->width - frmt->len);
	if (!(n == 0 && frmt->prec <= 0) ||
			!(frmt->base == 8 && (frmt->fl & SHARP)))
		itoa_base(frmt, n, str);
	print_all(frmt, str, frmt->len);
	if (frmt->fl & MINUS)
		padding(frmt, ' ', frmt->width - frmt->len);
}

void	print_bxou(t_format *frmt)
{
	uintmax_t n;

	if (frmt->fl & INTMAX)
		n = va_arg(frmt->ap, uintmax_t);
	else if (frmt->fl & SIZE_T)
		n = (size_t)va_arg(frmt->ap, size_t);
	else if (frmt->fl & LLONG)
		n = va_arg(frmt->ap, unsigned long long);
	else if (frmt->fl & LONG)
		n = va_arg(frmt->ap, unsigned long);
	else if (frmt->fl & SHORT)
		n = (unsigned short)va_arg(frmt->ap, unsigned int);
	else if (frmt->fl & SSHORT)
		n = (unsigned char)va_arg(frmt->ap, unsigned int);
	else
		n = va_arg(frmt->ap, unsigned int);
	settings_bxou(n, frmt);
}
