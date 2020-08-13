/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:47:17 by jbrigett          #+#    #+#             */
/*   Updated: 2019/09/11 19:12:49 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*save;

	save = NULL;
	while (*s)
	{
		if (*s == (char)c)
			save = s;
		s++;
	}
	if (!c)
		save = s;
	return ((char *)save);
}
