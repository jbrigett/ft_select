/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_aefg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:53:24 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/16 19:08:51 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_aefg(t_format *frmt)
{
	long double n;

	if (frmt->fl & LDOUBLE)
		n = (long double)va_arg(frmt->ap, long double);
	else
		n = (double)va_arg(frmt->ap, double);
	(!(frmt->fl & PRECISION)) ? frmt->prec = 6 : 0;
	frmt->pref = "";
	if (frmt->spec == 'f')
		print_f(frmt, n);
	else if (frmt->spec == 'a')
	{
		frmt->pref = (frmt->fl & UPPER) ? "0X" : "0x";
		print_ae(frmt, n);
	}
	else if (frmt->spec == 'g')
		print_g(frmt, n);
	else if (frmt->spec == 'e')
		print_ae(frmt, n);
}
