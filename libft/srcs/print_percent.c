/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 15:02:35 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/21 15:02:41 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_percent(t_format *frmt)
{
	if (!(frmt->fl & MINUS) && frmt->width > 1)
		padding(frmt, (frmt->fl & ZERO) ? '0' : ' ', frmt->width - 1);
	print_all(frmt, "%", 1);
	if (frmt->fl & MINUS && frmt->width > 0)
		padding(frmt, ' ', frmt->width - 1);
}
