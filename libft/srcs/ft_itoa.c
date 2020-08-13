/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 17:33:42 by jbrigett          #+#    #+#             */
/*   Updated: 2019/09/16 17:59:16 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_sizenum(unsigned int n)
{
	unsigned int	size;

	size = 1;
	while (n >= 10)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char			*ft_itoa(int n)
{
	unsigned int	in;
	unsigned int	size;
	char			*fresh;
	int				fl;

	in = (unsigned int)(n * (n < 0 ? -1 : 1));
	fl = (n < 0 ? 1 : 0);
	size = ft_sizenum(in) + fl;
	fresh = (char*)malloc(sizeof(char) * size + 1);
	if (!fresh)
		return (NULL);
	if (fl == 1)
		fresh[0] = '-';
	fresh[size--] = '\0';
	while (in >= 10)
	{
		fresh[size--] = in % 10 + '0';
		in /= 10;
	}
	fresh[size] = in % 10 + '0';
	return (fresh);
}
