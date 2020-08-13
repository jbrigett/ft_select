/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:40:42 by jbrigett          #+#    #+#             */
/*   Updated: 2019/09/16 21:14:33 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*t;

	if (alst)
	{
		t = *alst;
		while (t)
		{
			tmp = t->next;
			ft_lstdelone(&t, del);
			t = tmp;
		}
		*alst = NULL;
	}
}
