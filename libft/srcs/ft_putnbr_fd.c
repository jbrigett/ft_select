/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:49:38 by jbrigett          #+#    #+#             */
/*   Updated: 2019/09/18 15:19:11 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int res;

	res = (n < 0 ? -n : n);
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (res > 9)
	{
		ft_putnbr_fd((res / 10), fd);
		ft_putchar_fd((res % 10 + '0'), fd);
	}
	else
		ft_putchar_fd((res + '0'), fd);
}
