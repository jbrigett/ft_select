/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:36:31 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/17 16:36:32 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	get_size(int flag)
{
	struct winsize	term;

	ioctl(STDERR_FILENO, TIOCGWINSZ, &term);
	return ((flag) ? term.ws_col : term.ws_row);
}