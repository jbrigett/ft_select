/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_shandlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:33:01 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/17 16:33:02 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	sl_quit(int s)
{
	t_select *sl;

	sl = NULL;
	sl = get_t_select(&sl);
//	sl_restore(sl);
//	free_args(sl);
	exit(s);
}

void    sl_suspend(int s)
{
	struct termios	t_attr;
	char			susp[2];

	(void)s;
	if (tcgetattr(0, &t_attr) == -1)
		exit(-1);
	susp[0] = t_attr.c_cc[VSUSP];
	susp[1] = 0;
	t_attr.c_lflag |= ICANON;
	t_attr.c_lflag |= ECHO;
	t_attr.c_oflag |= OPOST;
	if (tcsetattr(0, TCSADRAIN, &t_attr) == -1)
		exit(1);
	ft_putstr_fd(tgetstr("ve", NULL), 2);
	ft_putstr_fd(tgetstr("te", NULL), 2);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, susp);
}

void	sl_restart(int s)
{
	t_select    *sl;
	char		buf[2];

	(void)s;
	sl = NULL;
	sl = get_t_select(&sl);
	tcgetattr(0, &sl->new_attr);
	sl->new_attr.c_lflag &= ~(ICANON | ECHO);
	sl->new_attr.c_oflag &= ~(OPOST);
	sl->new_attr.c_cc[VMIN] = 1;
	sl->new_attr.c_cc[VTIME] = 0;
	tcsetattr(sl->fd, TCSANOW, &sl->new_attr);
	if (tgetent(NULL, getenv("TERM")) <= 0)
		exit(1);
	sl_signals(sl);
	ft_putstr_fd(tgetstr("vi", NULL), 0);
	ft_putstr_fd(tgetstr("ti", NULL), 0);
	buf[0] = -62;
	buf[1] = 0;
	ioctl(0, TIOCSTI, buf);
}

void	sl_resize(int s)
{
	t_select *sl;

	(void)s;
	sl = NULL;
	sl = get_t_select(&sl);
	if (tgetent(NULL, getenv("TERM")) <= 0)
		sl_quit(0);
	sl_print(sl);
}