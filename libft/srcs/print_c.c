/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:53:50 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/22 18:26:33 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Алгоритм кодирования в UTF-8 стандартизирован в RFC 3629 и состоит из
** 3 этапов
**
** 1.Определить количество октетов (байтов), требуемых для кодирования символа
** 00000000-0000007F - 1  байт
** 00000080-000007FF - 2 байта
** 00000800-0000FFFF - 3 байта
** 00010000-0010FFFF - 4 байта
**
** 2. Установить старшие биты первого октета в соответствии с необходимым
** количеством октетов, определённом на первом этапе:
** 0xxxxxxx — если для кодирования потребуется один октет;
** 110xxxxx — если для кодирования потребуется два октета;
** 1110xxxx — если для кодирования потребуется три октета;
** 11110xxx — если для кодирования потребуется четыре октета.
**
** Если для кодирования требуется больше одного октета, то в октетах 2-4
** два старших бита всегда устанавливаются равными 10xxxxxx
*/

void		oct_4(wint_t c, t_format *frmt)
{
	unsigned char oct[4];

	oct[0] = (c >> 18) + 240;
	oct[1] = ((c >> 12) & 0x3F) | 0x80;
	oct[2] = ((c >> 6) & 0x3F) | 0x80;
	oct[3] = ((c & 0x3F) | 0x80);
	write(1, oct, 4);
	frmt->to_print += 4;
}

void		oct_3(wint_t c, t_format *frmt)
{
	unsigned char oct[3];

	oct[0] = (c >> 12) + 224;
	oct[1] = ((c >> 6) & 63) | 0x80;
	oct[2] = ((c & 0x3F) | 0x80);
	write(1, oct, 3);
	frmt->to_print += 3;
}

void		oct_2(wint_t c, t_format *frmt)
{
	unsigned char oct[2];

	oct[0] = (c >> 6) + 192;
	oct[1] = ((c & 0x3F) | 0x80);
	write(1, oct, 2);
	frmt->to_print += 2;
}

void		print_wchar(wint_t c, t_format *frmt)
{
	if (c <= 0x7F)
	{
		frmt->len = 1;
		write(1, &c, 1);
		frmt->to_print += 1;
	}
	if (c >= 0x80 && c <= 0x7FF)
	{
		frmt->len = 2;
		oct_2(c, frmt);
	}
	if (c >= 0x800 && c <= 0xFFFF)
	{
		frmt->len = 3;
		oct_3(c, frmt);
	}
	if (c >= 0x10000 && c <= 0x1FFFFF)
	{
		frmt->len = 4;
		oct_4(c, frmt);
	}
}

void		print_c(t_format *frmt)
{
	wint_t c;

	if (frmt->fl & LONG)
		c = (wchar_t)va_arg(frmt->ap, wint_t);
	else
		c = (char)va_arg(frmt->ap, int);
	c = (wint_t)c;
	frmt->width = (frmt->width > 0) ? frmt->width - ft_wcharlen(c) : 0;
	if (!(frmt->fl & MINUS) && frmt->width > 0)
		padding(frmt, (frmt->fl & ZERO) ? '0' : ' ', frmt->width);
	print_wchar(c, frmt);
	if (frmt->fl & MINUS && frmt->width > 0)
		padding(frmt, ' ', frmt->width);
}
