/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:35:17 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/17 16:35:19 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	move_up(t_select *sl)
{
	int		i;
	t_args	*tmp;

	i = 0;
	tmp = sl->cur;
	while (++i < sl->cols)
		tmp = tmp->prev;
	sl->cur = tmp->prev;
}

void	move_down(t_select *sl)
{
	int		i;
	t_args	*tmp;

	i = 0;
	tmp = sl->cur;
	while (++i < sl->cols)
		tmp = tmp->next;
	sl->cur = tmp->next;
}