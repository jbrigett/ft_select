/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:22:15 by jbrigett          #+#    #+#             */
/*   Updated: 2019/09/18 14:33:15 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, char const *needle)
{
	int i;
	int tmp;

	if (!*needle)
		return ((char*)haystack);
	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			tmp = 1;
			while (needle[tmp] != '\0' && haystack[tmp + i] == needle[tmp])
				++tmp;
			if (needle[tmp] == '\0')
				return ((char*)&haystack[i]);
		}
		++i;
	}
	return (NULL);
}
