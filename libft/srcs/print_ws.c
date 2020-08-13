/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ws.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:55:22 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/22 18:27:03 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_wcharlen(wint_t c)
{
	if (c <= 0x7F)
		return (1);
	if (c >= 0x80 && c <= 0x7FF)
		return (2);
	if (c >= 0x80 && c <= 0xFFFF)
		return (3);
	if (c >= 0x10000 && c <= 0x1FFFFF)
		return (4);
	return (4);
}

void	print_wstring(wchar_t *wstr, t_format *frmt, int64_t strlen)
{
	while ((strlen -= ft_wcharlen(*wstr)) >= 0)
		print_wchar(*wstr++, frmt);
}

int64_t	wslen(wchar_t *wstr, t_format *frmt)
{
	intmax_t	len;
	intmax_t	strlen;

	strlen = 0;
	len = frmt->prec;
	while (*wstr != L'\0')
	{
		if (frmt->fl & PRECISION && ft_wcharlen(*wstr) > (size_t)len)
			break ;
		strlen += ft_wcharlen(*wstr);
		len -= ft_wcharlen(*wstr);
		++wstr;
	}
	len = strlen;
	return (len);
}

void	print_ws(t_format *frmt)
{
	wchar_t	*wstr;

	if (!(wstr = (wchar_t *)va_arg(frmt->ap, wchar_t *)))
		print_null(frmt);
	frmt->len = wslen(wstr, frmt);
	if (!(frmt->fl & MINUS))
		padding(frmt, (frmt->fl & ZERO) ? '0' : ' ', frmt->width - frmt->len);
	print_wstring(wstr, frmt, frmt->len);
	if (frmt->fl & MINUS)
		padding(frmt, ' ', frmt->width - frmt->len);
}
