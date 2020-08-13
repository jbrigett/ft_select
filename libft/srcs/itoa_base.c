/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:52:33 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/06 13:29:14 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	itoa_base(t_format *frmt, uintmax_t n, char *str)
{
	char	*print;
	size_t	tmp;

	print = "0123456789abcdef";
	(frmt->fl & UPPER) ? print = "0123456789ABCDEF" : 0;
	tmp = frmt->len;
	while (tmp--)
	{
		str[tmp] = print[n % frmt->base];
		n /= frmt->base;
	}
}

void	print_itoa_base(uintmax_t n, t_format *frmt)
{
	uintmax_t	tmp;
	size_t		len;
	char		str[40];

	len = 1;
	tmp = 33;
	while (tmp-- > 0)
		str[tmp] = 0;
	tmp = n;
	while ((tmp /= frmt->base) > 0)
		++len;
	if ((n == 0) && frmt->fl & PRECISION && (frmt->prec == 0)
			&& frmt->spec != 'f')
		str[0] = '\0';
	else if (n == 0)
		str[0] = '0';
	else
	{
		frmt->len = len;
		itoa_base(frmt, n, str);
	}
	print_all(frmt, str, ft_strlen(str));
}
