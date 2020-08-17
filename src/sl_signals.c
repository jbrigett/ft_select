#include "ft_select.h"


/*
** Добавить стаиическою переменну/ в фт_эезит наверно
*/
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

void		sl_signals(void)
{
	int sig;

	sig = 0;
	while (++sig < 32)
		signal(sig, signal_handler);
}
