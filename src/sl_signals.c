/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:15:53 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/17 16:15:55 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	signal_handler(int s)
{
//	if (s == SIGTSTP)
//		ft_suspend(s);
//	else if (s == SIGCONT)
//		ft_continue(s);
	if (s == SIGWINCH)
		sl_resize(s);
	else
		sl_quit(s);
}

t_select	*get_t_select(t_select **t)
{
	static t_select *tmp;

	if (*t == NULL)
		return (tmp);
	tmp = *t;
	return (*t);
}

void		sl_signals(t_select	*sl)
{
	int s;

	sl = get_t_select(&sl);
	s = 0;
	while (++s < 32)
		signal(s, signal_handler);
}