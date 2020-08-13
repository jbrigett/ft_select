/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 15:02:18 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/21 15:02:23 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_all(t_format *frmt, char *str, int len)
{
	int i;

	i = 0;
	len > 0 ? frmt->to_print += len : 0;
	while (i < len)
	{
		write(frmt->fd, str, 1);
		str++;
		i++;
	}
}

void	padding(t_format *frmt, char c, int len)
{
	int i;

	i = 0;
	len > 0 ? frmt->to_print += len : 0;
	while (i < len)
	{
		write(frmt->fd, &c, 1);
		i++;
	}
}
