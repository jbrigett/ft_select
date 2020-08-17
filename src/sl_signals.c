#include "ft_select.h"


/*
** Добавить стаиическою переменну/ в фт_эезит наверно
*/

void	finish(int s)
{
	t_ttyset *t;

	t = NULL;
	t = old_settings(&t);
	normal_mode(t);
	t->term.c_lflag |= (ICANON | ECHO);
	t->term.c_oflag |= OPOST;
	tcsetattr(t->fd, TCSANOW, &t->term);
	(s == -1) ? 0 : ft_putstr_fd(CL, 0);
	ft_putstr_fd(VE, 0);
	close(t->fd);
	free(t->selected);
	free(t);
	exit(s);
}

static void	suspend(int s)
{
	struct termios	t_attr;
	char			susp[2];

	(void)s;
	if (tcgetattr(0, &t_attr) == -1)
		ERROR_EXIT;
	susp[0] = t_attr.c_cc[VSUSP];
	susp[1] = 0;
	t_attr.c_lflag |= ICANON;
	t_attr.c_lflag |= ECHO;
	t_attr.c_oflag |= OPOST;
	if (tcsetattr(0, TCSADRAIN, &t_attr) == -1)
		ERROR_EXIT;
	ft_putstr_fd(VE, 2);
	ft_putstr_fd(TE, 2);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, susp);
}

static void	restart(int s)
{
	t_ttyset	*t;
	char		buf[2];

	(void)s;
	t = NULL;
	t = old_settings(&t);
	tcgetattr(t->fd, &t->term);
	t->term.c_lflag &= ~(ICANON | ECHO);
	t->term.c_oflag &= ~(OPOST);
	t->term.c_cc[VMIN] = 1;
	t->term.c_cc[VTIME] = 0;
	tcsetattr(t->fd, TCSANOW, &t->term);
	if (tgetent(NULL, getenv("TERM")) <= 0)
		ERROR_EXIT;
	setsigs(t);
	ft_putstr_fd(VI, 0);
	ft_putstr_fd(TI, 0);
	buf[0] = -62;
	buf[1] = 0;
	ioctl(0, TIOCSTI, buf);
}

static void	size_changed(int s)
{
	t_ttyset *t;

	(void)s;
	t = NULL;
	t = old_settings(&t);
	if (tgetent(NULL, getenv("TERM")) <= 0)
		ERROR_EXIT;
	print_items(t);
}

static void	signal_handler(int s)
{
	else if (s == SIGTSTP)
		ft_suspend();
	else if (s == SIGCONT)
		ft_continue();
	else if (s == SIGWINCH)
		ft_resize();
	else
		ft_quit();
}


t_select	*old_settings(t_select **t)
{
	static t_select *tmp;

	if (*t == NULL)
		return (tmp);
	tmp = *t;
	return (*t);
}

void		sl_signals(t_select	*sl);
{
	int sig;

	sl =
	sig = 0;
	while (++sig < 32)
		signal(sig, signal_handler);
}