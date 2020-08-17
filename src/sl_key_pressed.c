/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_key_pressed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:15:41 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/17 16:15:46 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	on_key_pressed(t_select *sl)
{
	long		c;

	while (21)
	{
//		column_display();
		c = 0;
		read(STDERR_FILENO, &c, 8);
		if (c == ENTER_K)
			break ;
		else if (c == UP_K)
			ft_printf("  UP  ");
		else if (c == DOWN_K)
			ft_printf("  DOWN  ");
/*		else if (c == SPC_KEY)
			toggle_selection();
		else if (c == ESC_KEY)
			stop_signal_handler();
		else if (c == BSP_KEY || c == DEL_KEY)
			delete_active_arg();
		else if (c == STAR_KEY || c == MINUS_KEY)
			toggle_all_args(c);
		else if (c == O_KEY || c == B_KEY)
			folder_browsing(c);
		else
			move(get_dir(c)); */
	}
}
