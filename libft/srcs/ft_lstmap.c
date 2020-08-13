/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:57:11 by jbrigett          #+#    #+#             */
/*   Updated: 2019/09/18 18:10:06 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*cur;
	t_list	*prev;
	t_list	*fresh;

	fresh = NULL;
	if (!f || !lst)
		return (NULL);
	while (lst)
	{
		cur = f(ft_lstnew(lst->content, lst->content_size));
		if (fresh)
		{
			prev->next = cur;
			prev = cur;
		}
		else
		{
			fresh = cur;
			prev = fresh;
		}
		lst = lst->next;
	}
	return (fresh);
}
