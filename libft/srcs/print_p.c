/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 15:03:54 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/21 15:03:57 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_p(t_format *frmt)
{
	void		*ptr;
	uintmax_t	nb;

	ptr = va_arg(frmt->ap, void *);
	nb = (uintmax_t)ptr;
	frmt->base = 16;
	frmt->pref = "0x";
	frmt->fl |= POINTER;
	frmt->fl |= SHARP;
	settings_bxou(nb, frmt);
}
