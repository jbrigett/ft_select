/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:55:35 by jbrigett          #+#    #+#             */
/*   Updated: 2020/07/16 19:23:42 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wchar_t	*wstrndup(wchar_t *s1, size_t n)
{
	wchar_t	*s2;
	size_t	i;

	i = 0;
	if (!(s2 = (wchar_t *)malloc(sizeof(wchar_t) * n + 1)))
		exit(-1);
	while (s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = L'\0';
	return (s2);
}

wchar_t	*wstrdup(wchar_t *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	return (wstrndup(str, len));
}

void	print_null(t_format *frmt)
{
	wchar_t *wstr;
	int		i;

	i = 0;
	wstr = wstrdup(L"(null)");
	if (frmt->prec > -1)
		while (wstr[i] && frmt->prec-- > 0)
			print_wchar(wstr[i++], frmt);
	else
		while (wstr[i])
			print_wchar(wstr[i++], frmt);
	free(wstr);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;
	size_t	i;

	i = 0;
	if (!(s2 = ft_strnew(n)))
		return (NULL);
	while (s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}
