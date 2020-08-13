/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:57:24 by jbrigett          #+#    #+#             */
/*   Updated: 2019/09/18 21:15:55 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	unsigned int pos;
	unsigned int i;

	if (!*s2)
		return ((char*)s1);
	pos = 0;
	while (s1[pos] != '\0' && (size_t)pos < len)
	{
		if (s1[pos] == s2[0])
		{
			i = 1;
			while (s2[i] != '\0' && s1[pos + i] == s2[i] &&
					(size_t)(pos + i) < len)
				++i;
			if (s2[i] == '\0')
				return ((char*)&s1[pos]);
		}
		++pos;
	}
	return (0);
}
