/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:18:48 by jbrigett          #+#    #+#             */
/*   Updated: 2019/09/18 18:23:17 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_numwords(char const *s, char c)
{
	size_t	i;
	int		fl;

	i = 0;
	fl = 0;
	while (*s)
	{
		if (fl == 0 && *s != c)
		{
			fl = 1;
			++i;
		}
		else if (fl == 1 && *s == c)
			fl = 0;
		s++;
	}
	return (i);
}

static size_t	ft_strlenword(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

static void		ft_arrclr(char ***s)
{
	char **res;

	res = *s;
	while (res != NULL)
	{
		ft_strdel(&(*res));
		(*res)++;
	}
	free(res);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	num;
	int		i;
	char	**res;

	if (!s)
		return (NULL);
	num = ft_numwords(s, c);
	res = (char**)malloc(sizeof(*res) * (num + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (num--)
	{
		while (*s == c && *s != '\0')
			s++;
		res[i] = ft_strsub(s, 0, ft_strlenword(s, c));
		if (!res[i++])
		{
			ft_arrclr(&res);
			return (NULL);
		}
		s += ft_strlenword(s, c);
	}
	res[i] = NULL;
	return (res);
}
