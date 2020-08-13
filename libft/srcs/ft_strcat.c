/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:20:30 by jbrigett          #+#    #+#             */
/*   Updated: 2019/09/18 21:30:02 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	if (ft_strlen(s2) + 1 == 0)
		return (NULL);
	ft_memcpy(s1 + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (s1);
}
