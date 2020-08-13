/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:51:04 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/21 15:03:40 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	t_format	*frmt;
	char		*str;

	if (!(frmt = (t_format*)malloc(sizeof(t_format))))
		return (-1);
	init_format(1, frmt, format);
	str = (char*)format;
	if (format)
	{
		va_start(frmt->ap, format);
		while (*str != '\0')
		{
			if (*str == '%')
				parser(&str, frmt);
			else
			{
				write(1, str, 1);
				str++;
				frmt->to_print++;
			}
		}
		va_end(frmt->ap);
	}
	free(frmt);
	return (frmt->to_print);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	t_format	*frmt;
	char		*str;

	if (!(frmt = (t_format*)malloc(sizeof(t_format))))
		return (-1);
	init_format(fd, frmt, format);
	str = (char*)format;
	if (format)
	{
		va_start(frmt->ap, format);
		while (*str != '\0')
		{
			if (*str == '%')
				parser(&str, frmt);
			else
			{
				write(fd, str, 1);
				str++;
				frmt->to_print++;
			}
		}
		va_end(frmt->ap);
	}
	free(frmt);
	return (frmt->to_print);
}
