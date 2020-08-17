/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:15:26 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/17 16:15:27 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int8_t	sl_check_extention(char *value, const char *ext)
{
	int	i;

	if ((i = ft_strchr_index(value, '.')) < 0)
		return (0);
	if (ft_strequ(value + i, ext))
		return (1);
	else
		return (0);
}

/*
** first we find last '/' to get th name
** str_index return '.' then we check if the end of the string is same as .a etc
*/
void	set_type(t_args *sl, char *value)
{
	char	*name;

	sl->value = ft_strdup(value);
	sl->type = 6;
	name = ft_strrchr(value, '/') ? ft_strrchr(value, '/') + 1 : value;
	if (name[0] == '.')
	{
		sl->type = 5;
		return ;
	}
	(sl_check_extention(name, ".c")) ? sl->type = 0 : 0;
	(sl_check_extention(name, ".o")) ? sl->type = 1 : 0;
	(sl_check_extention(name, ".h")) ? sl->type = 2 : 0;
	(sl_check_extention(name, ".a")) ? sl->type = 3 : 0;
	(ft_strequ(name, "Makefile")) ? sl->type = 4 : 0;
}

void	new_arg(t_select *sl, char *value)
{
	t_args		*cur;
	t_args		*prev;

	if (!(cur = (t_args *)ft_memalloc(sizeof(t_args))))
		exit(1);
	set_type(cur, value);
	if (!(sl->arg))
	{
		cur->prev = cur;
		cur->next = cur;
		sl->arg = cur;
		sl->cur = sl->arg;
		return ;
	}
	prev = sl->arg->prev;
	cur->next = sl->arg;
	sl->arg->prev = cur;
	cur->prev = prev;
	prev->next = cur;
}

void	delete_arg(t_select *sl)
{
	t_args		*active;

	if (!sl->cur)
		return ;
	active = sl->cur;
	if (sl->arg == active)
		sl->arg = (active->next == active) ? NULL : active->next;
	else
		sl->cur = active->next;
	active->next->prev = active->prev;
	active->prev->next = active->next;
//	system_delete_arg(active->value);
	sl->argc--;
	free(active->value);
	active->value = NULL;
	free(active);
	active = NULL;
//	if (!sl->argc)
//		stop_signal_handler();
}

void	free_args(t_select *sl)
{
	t_args		*first;
	t_args		*cur;

	first = sl->arg;
	while (sl->arg)
	{
		cur = sl->arg;
		free(sl->arg->value);
		sl->arg->value = NULL;
		sl->argc--;
		if (sl->arg->next == first)
			break ;
		sl->arg = sl->arg->next;
		free(cur);
		cur = NULL;
	}
	if (cur)
	{
		free(cur);
		cur = NULL;
	}
	sl->arg = NULL;
}