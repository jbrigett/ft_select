/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_found.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 15:01:17 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/04 17:01:08 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	cs_not_found(t_format *frmt)
{
	if (!frmt->spec)
		return ;
	frmt->width = (frmt->width > 0) ? frmt->width - 1 : 0;
	if (frmt->fl & MINUS)
		padding(frmt, (frmt->fl & ZERO) ? '0' : ' ', frmt->width);
	print_all(frmt, &frmt->spec, 1);
	if (frmt->fl & ZERO)
		padding(frmt, ' ', frmt->width);
}
