/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_look.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:33:29 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/17 16:33:32 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_select.h"

int		get_cols(t_select *sl)
{
	int count;

	count = get_size(1) / (get_max_len(sl) + 1);
	(!count) ? count = 1 : 0;
	((get_max_len(sl) + 1) * sl->argc < get_size(1)) ? count = sl->argc : 0;
	return (count);
}

int		get_max_len(t_select *sl)
{
	int		max;
	int		len;
	t_args	*first;
	t_args	*tmp;

	if (!sl->arg || !sl->arg->value)
		return (0);
	max = 0;
	tmp = sl->arg;
	first = tmp;
	while (tmp)
	{
		((len = ft_strlen(tmp->value)) > max) ? max = len : 0;
		if (tmp->next == first)
			break ;
		tmp = tmp->next;
	}
	return (max);
}

void    print_color(t_args *arg)
{
	(arg->type == 0) ? ft_putstr_fd(CT_COL, 2) : 0;
	(arg->type == 1) ? ft_putstr_fd(OT_COL, 2) : 0;
	(arg->type == 2) ? ft_putstr_fd(HT_COL, 2) : 0;
	(arg->type == 3) ? ft_putstr_fd(AT_COL, 2) : 0;
	(arg->type == 4) ? ft_putstr_fd(MT_COL, 2) : 0;
	(arg->type == 5) ? ft_putstr_fd(DT_COL, 2) : 0;
	ft_putstr_fd(arg->value, 2);
	ft_putstr_fd(ST_COL, 2);
}

void	print_args(t_args *first, t_select *sl)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (++i < sl->rows)
	{
		j = -1;
		while (++j < sl->cols)
		{
			(sl->arg == (sl->cur)) ? ft_putstr_fd(UN_COL, 2) : 0;
			(sl->arg->select) ? ft_putstr_fd(RV_COL, 2) : 0;
			print_color(sl->arg);
			len = ft_strlen(sl->arg->value);
			while (len++ <= get_max_len(sl))
				ft_putstr_fd(" ", 2);
			if (sl->arg->next == first)
				break ;
			sl->arg = sl->arg->next;
		}
		ft_putstr_fd("\n", 2);
	}
}

void	sl_print(t_select *sl)
{
	if (!sl->arg || get_max_len(sl) > get_size(1))
		return ;
	tputs(tgetstr("cl", NULL), 1, ft_putc);
	sl->cols = get_cols(sl);
	sl->rows = sl->argc / sl->cols;
	if (sl->rows > get_size(0))
		return ;
	(sl->argc % sl->cols) ? sl->rows += 1 : 0;
	print_args(sl->arg, sl);
}