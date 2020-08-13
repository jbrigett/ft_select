/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:49:17 by jbrigett          #+#    #+#             */
/*   Updated: 2019/09/08 15:15:38 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	len;
	char	*fresh;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	fresh = (char*)malloc(sizeof(*fresh) * (len + 1));
	if (!fresh)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
	{
		fresh[len] = f(s[len]);
		len++;
	}
	fresh[len] = '\0';
	return (fresh);
}
