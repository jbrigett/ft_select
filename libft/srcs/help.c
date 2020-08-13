/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:51:18 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/21 14:59:52 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	ft_max(intmax_t a, intmax_t b)
{
	return (a > b ? a : b);
}

void		init_format(int fd, t_format *format, const char *str)
{
	format->width = 0;
	format->len = 0;
	format->fd = fd;
	format->prec = 1;
	format->to_print = 0;
	format->spec = '\0';
	format->base = 0;
	format->str = str;
	format->fl = 0;
}

void		reinit_format(t_format *format)
{
	format->fl = 0;
	format->width = 0;
	format->prec = 1;
	format->spec = '\0';
	format->base = 0;
	format->len = 0;
}

int8_t		ft_isupper(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int			ft_strchr_index(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		++i;
	}
	return (-1);
}
