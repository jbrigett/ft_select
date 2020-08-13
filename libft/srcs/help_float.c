/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:50:44 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/22 18:23:14 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	ft_fabsl(long double d)
{
	return (d < 0 ? -d : d);
}

uintmax_t	ft_imaxabs(intmax_t d)
{
	intmax_t mask;

	mask = (d >> (sizeof(d) * CHAR_BIT - 1));
	d = (uintmax_t)((d + mask) ^ mask);
	return (d);
}

intmax_t	ft_roundl(long double d, int32_t prec)
{
	intmax_t	integ;
	long double	fract;

	integ = (intmax_t)d;
	fract = d - integ;
	if (fract <= -0.5 && d < 0 && prec != 0)
		return (integ - 1);
	else if (fract >= 0.5 && d > 0 && prec != 0)
		return (integ + 1);
	if (fract < -0.5 && d < 0 && prec == 0)
		return (integ - 1);
	else if (fract > 0.5 && d > 0 && prec == 0)
		return (integ + 1);
	else
		return (integ);
}

size_t		length_base(uintmax_t n, int8_t base)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}
