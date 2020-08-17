/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_hz.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 18:34:08 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/17 18:34:09 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"


void	reset_default_conf(void)
{
	tcsetattr(STDERR_FILENO, TCSANOW, &g_select.old_attr);
	tputs(tgetstr("ve", NULL), 1, ft_printnbr);
	tputs(tgetstr("te", NULL), 1, ft_printnbr);
}




static void	ft_print_arg_single_column(char *arg, int index)
{
	if (g_sel.cursor == index)
		tputs(tgetstr("us", NULL), 1, ft_putc);
	if (g_sel.selected[index] == SELECTED)
		tputs(tgetstr("mr", NULL), 1, ft_putc);
	ft_dprintf(g_sel.fd, "%s\n", arg);
	if (g_sel.color)
		ft_color(index);
	else
		ft_dprintf(g_sel.fd, "\033[0m");
}

/*
** Display all arguments in a single column if the window's height is sufficient
** Display only if the window's width is larger than any argument
*/

void		ft_display(void)
{
	int i;

	i = 0;
	if ((int)ft_tablen(g_sel.args) < g_sel.rows && ft_max_arglen() < g_sel.cols)
	{
		while (i < (int)ft_tablen(g_sel.args))
		{
			ft_print_arg_single_column(g_sel.args[i], i);
			i++;
		}
	}
	else if (ft_max_arglen() > g_sel.cols)
		ft_dprintf(g_sel.fd, "Window\nsize\nis\ntoo\nsmall\n🖼");
	else
		ft_display_multi_column();
}

void		ft_display_selection(void) {
	int i;
	int j;

	i = 0;
	j = 0;
	while (g_sel.args[i]) {
		if (g_sel.selected[i] == SELECTED)
			j = ft_dprintf(1, "%s", g_sel.args[i]);
		if (g_sel.args[i + 1] && g_sel.selected[i + 1] == SELECTED && j)
			ft_dprintf(1, " ");
		i++;
	}
}

static void	ft_print_arg_multi_column(char *arg, int index)
{
	if (g_sel.cursor == index)
		tputs(tgetstr("us", NULL), 1, ft_putc);
	if (g_sel.selected[index] == SELECTED)
		tputs(tgetstr("mr", NULL), 1, ft_putc);
	ft_dprintf(g_sel.fd, "%s", arg);
	if (g_sel.color)
		ft_color(index);
	else
		ft_dprintf(g_sel.fd, "\033[0m");
}

/*
** Storing of the total length of arguments printed in the current line
** Checking if the next argument still fits in the current line
** If not, go the next line
*/

static void	ft_display_multi_column2(void)
{
	int i;
	int line;

	i = 1;
	line = (int)ft_strlen(g_sel.args[0]);
	ft_print_arg_multi_column(g_sel.args[0], 0);
	while (g_sel.args[i])
	{
		if (line + (int)ft_strlen(g_sel.args[i]) < g_sel.cols)
		{
			ft_dprintf(g_sel.fd, " ");
			ft_print_arg_multi_column(g_sel.args[i], i);
		}
		else
		{
			ft_dprintf(g_sel.fd, "\n");
			ft_print_arg_multi_column(g_sel.args[i], i);
			line = 0;
		}
		line += (int)ft_strlen(g_sel.args[i]);
		line++;
		i++;
	}
}

/*
** Calculation to verify that the window's size is large enough to fit all args
*/

void		ft_display_multi_column(void)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (g_sel.args[i])
	{
		len += (int)ft_strlen(g_sel.args[i]);
		len++;
		i++;
	}
	if (len > (g_sel.cols * g_sel.rows) * 0.87)
		ft_dprintf(g_sel.fd, "Window\nsize\nis\ntoo\nsmall\n🖼");
	else
		ft_display_multi_column2();
}


