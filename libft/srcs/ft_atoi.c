/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 16:04:51 by jbrigett          #+#    #+#             */
/*   Updated: 2019/09/11 19:24:20 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	tmp;
	long long	res;
	int			signe;

	while (ft_isspace(*str))
		str++;
	signe = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	res = 0;
	while (ft_isdigit(*str))
	{
		tmp = res;
		res = res * 10 + (*str - '0');
		if (tmp != (res - (*str - '0')) / 10 || res < 0)
			return (-1 * (signe + 1) / 2);
		str++;
	}
	return (signe < 0 ? -res : res);
}
