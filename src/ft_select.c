/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 19:11:10 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/17 18:40:11 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_exit(t_select *sl, int status)
{
	free_args(sl);
	exit(status);
}

int		main(int argc, char **argv, char **env)
{
	t_select	*sl;

	sl_errors(argc, argv, env);
	if (!(sl = (t_select *)malloc(sizeof(t_select))))
		exit(0);
	sl_init(sl, argc, argv);
	on_key_pressed(sl);
	ft_restore(sl);
	free_args(sl);
	return (0);
}
