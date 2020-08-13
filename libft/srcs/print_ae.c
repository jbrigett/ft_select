/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ae.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:53:14 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/22 18:29:50 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_exp(t_double *doub, t_format *frmt)
{
	doub->fraction = 0.0;
	doub->integer = 0;
	doub->exp = 0;
	if (doub->n != 0)
	{
		if (doub->n < 1)
			while (doub->n < 1)
			{
				doub->exp -= 1;
				doub->n *= (frmt->base == 10) ? frmt->base : 2;
			}
		else if (doub->n >= 1)
			while (doub->n > ((frmt->base == 10) ? frmt->base - 1 : 2))
			{
				doub->exp += 1;
				doub->n /= (frmt->base == 10) ? frmt->base : 2;
			}
		doub->integer = (uint64_t)doub->n;
		doub->fraction = doub->n - doub->integer;
	}
}

void	print_exp(int64_t exp, t_format *frmt)
{
	if (frmt->base == 16)
		print_all(frmt, (frmt->fl & UPPER) ? "P" : "p", 1);
	else
		print_all(frmt, (frmt->fl & UPPER) ? "E" : "e", 1);
	print_all(frmt, (exp >= 0) ? "+" : "-", 1);
	if (exp > -9 && exp < 9 && frmt->base == 10)
		print_all(frmt, "0", 1);
	print_itoa_base(ft_imaxabs(exp), frmt);
}

void	set_width_ae(t_double *d, t_format *frmt)
{
	if (d->sign || (frmt->fl & PLUS) || (frmt->fl & SPACE))
		frmt->width -= 1;
	if (frmt->fl & SHARP || frmt->prec > 0)
		frmt->width -= 1;
	frmt->width -= length_base(d->integer, frmt->base);
	frmt->width -= ft_strlen(frmt->pref);
	frmt->width -= (frmt->prec == 0) ? 0 : frmt->prec;
}

void	print_ae(t_format *frmt, long double d)
{
	uintmax_t	n;
	t_double	*doub;

	if (!(doub = (t_double*)malloc(sizeof(t_double))))
		return ;
	doub->n = d;
	set_exp(doub, frmt);
	(!(frmt->fl & PRECISION)) ? frmt->prec = 6 : 0;
	set_width_ae(doub, frmt);
	print_sign(doub, frmt);
	n = (frmt->prec == 0) ? ft_roundl(doub->integer + doub->fraction, 0)
		: doub->integer;
	print_itoa_base(n, frmt);
	if (frmt->fl & SHARP || frmt->prec > 0)
		print_fraction(doub, frmt);
	print_exp(doub->exp, frmt);
	if (frmt->fl & MINUS)
		padding(frmt, ' ', frmt->width);
}
