/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:16:01 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/17 16:16:02 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	The tcgetattr() function gets the parameters associated with the
**	terminal referred to by fildes and stores them in the termios
**	structure (see termio(7I)) referenced by termios_p.
**	The fildes argument is an open file descriptor associated with a terminal.
**	The termios_p argument is a pointer to a termios structure.
**
**  tcflag_t c_iflag;		input modes
**	tcflag_t c_oflag;		output modes
**	tcflag_t c_cflag;		control modes
**	tcflag_t c_lflag;		local modes
**	cc_t     c_cc[NCCS];	special characters
**
**	tcsetattr() sets the parameters associated with the terminal (unless
**	support is required from the underlying hardware that is not avail‐
**	able) from the termios structure referred to by termios_p.
**	optional_actions specifies when the changes take effect:
**
**	TCSANOW – the change occurs immediately.
**	TCSADRAIN - the change occurs after all output written to fd has been
**				transmitted.
**	TCSAFLUSH - the change occurs after all output written to the object
**				referred by fd has been transmitted, and all input that has
**				been received but not read will be discarded before the change
**				is made.
**
**	In NONcanonical mode input is available immediately (without the user
**	having to type a line-delimiter character), no input processing is
**	performed, and line editing is disabled.  The read buffer will only
**	accept 4095 chars; this provides the necessary space for a newline
**	char if the input mode is switched to canonical.  The settings of MIN
**	(c_cc[VMIN]) and TIME (c_cc[VTIME]) determine the circumstances in
**	which a read(2) completes; there are four distinct cases:
**
**	MIN == 0, TIME == 0 (polling read)
**	MIN > 0, TIME == 0 (blocking read)
**	MIN == 0, TIME > 0 (read with timeout)
**	MIN > 0, TIME > 0 (read with interbyte timeout)
**
**	Padding means outputting null characters following a terminal display
**	command that takes a long time to execute. The terminal description says
**	which commands require padding and how much; the function tputs,
**	described below, outputs a terminal command while extracting from it
**	the padding information, and then outputs the padding that is necessary.
**
** 	vi  -  Make cursor invisible
**	ve  -  Make cursor appear normal
**	cl  -  Clear screen and home cursor
*/

int		ft_putc(int c)
{
	return (write(1, &c, 1));
}

void	sl_init(t_select *sl, int argc, char **argv)
{
	int	i;

	i = 0;
	if ((sl->fd = open(ttyname(0), O_RDWR | O_NDELAY)) < 0)
		sl_quit(1);
	if (tcgetattr(sl->fd, &sl->old_attr) < 0)
		sl_quit(1);
	if (tcgetattr(sl->fd, &sl->new_attr) < 0)
		sl_quit(1);
	sl->new_attr.c_lflag &= ~(ICANON | ECHO);
	sl->new_attr.c_oflag &= ~(OPOST);
	sl->new_attr.c_cc[VMIN] = 1;
	sl->new_attr.c_cc[VTIME] = 0;
	if (tcsetattr(sl->fd, TCSANOW, &sl->new_attr) < 0)
		sl_quit(1);
	sl->amount = 0;
	ft_putstr_fd(tgetstr("vi", NULL), 0);
	sl->argc = argc;
	while(argv[++i])
		new_arg(sl, argv[i]);
}

void	sl_restore(t_select *sl)
{
	if (tcsetattr(sl->fd, TCSANOW, &sl->old_attr) < 0)
		sl_quit(1);
}

