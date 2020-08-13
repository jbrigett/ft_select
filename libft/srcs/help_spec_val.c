/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_spec_val.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 13:27:40 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/06 13:29:27 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	help_nan(t_format *frmt, uint64_t integ)
{
	if (!(frmt->fl & MINUS) && !(frmt->fl & ZERO))
		padding(frmt, ' ', frmt->width - 3);
	if (!(integ & LD_FRAC))
		print_all(frmt, (frmt->fl & UPPER) ? "INF" : "inf", 3);
	else
		print_all(frmt, (frmt->fl & UPPER) ? "NAN" : "nan", 3);
	if (frmt->fl & MINUS)
		padding(frmt, ' ', frmt->width - 3);
}

void	help_inf(t_format *frmt, uint64_t integ)
{
	if (!(frmt->fl & MINUS) && !(frmt->fl & ZERO))
		padding(frmt, ' ', frmt->width - 4);
	if (!(integ & LD_FRAC))
		print_all(frmt, (frmt->fl & UPPER) ? "-INF" : "-inf", 4);
	else
		print_all(frmt, (frmt->fl & UPPER) ? "-NAN" : "-nan", 4);
	if (frmt->fl & MINUS)
		padding(frmt, ' ', frmt->width - 4);
}
