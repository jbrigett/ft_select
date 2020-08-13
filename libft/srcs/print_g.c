/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_g.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:54:50 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/22 18:30:04 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int32_t	compare_fe(long double d, t_format *frmt)
{
	int64_t		tmp;
	t_double	*doub;

	if (!(doub = (t_double*)malloc(sizeof(t_double))))
		return (-1);
	doub->n = d;
	set_exp(doub, frmt);
	frmt->len = length_base((uintmax_t)ft_fabsl(d), 10);
	if ((intmax_t)frmt->len > frmt->prec || doub->exp <= -4)
	{
		frmt->prec -= (intmax_t)frmt->len;
		return (1);
	}
	frmt->prec += (doub->exp < 0) ? ft_imaxabs(doub->exp) : 0;
	tmp = frmt->len;
	doub->fraction = d - (intmax_t)d;
	while (doub->fraction < 0)
	{
		doub->fraction *= 10;
		doub->fraction -= (int64_t)doub->fraction;
		++tmp;
	}
	frmt->prec = (tmp < frmt->prec) ? tmp : frmt->prec - (intmax_t)frmt->len;
	return (0);
}

void	print_g(t_format *frmt, long double d)
{
	if (compare_fe(d, frmt))
		print_ae(frmt, d);
	else
		print_f(frmt, d);
}
