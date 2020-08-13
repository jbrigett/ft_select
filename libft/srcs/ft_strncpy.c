/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:18:13 by jbrigett          #+#    #+#             */
/*   Updated: 2019/09/18 20:08:34 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t size;

	size = ft_strlen(src);
	if (size >= len)
		ft_memcpy(dst, src, len);
	else
	{
		ft_memcpy(dst, src, size);
		ft_memset(dst + size, '\0', len - size);
	}
	return (dst);
}
