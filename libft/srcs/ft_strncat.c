/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:17:34 by jbrigett          #+#    #+#             */
/*   Updated: 2019/09/10 12:17:38 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char		*dst;
	const char	*src;

	if (n != 0)
	{
		dst = s1;
		src = s2;
		while (*dst)
			dst++;
		while (n-- != 0)
		{
			if ((*dst = *src++) == '\0')
				break ;
			dst++;
		}
		*dst = '\0';
	}
	return (s1);
}
