//
// Created by mort on 17/08/2020.
//

static void	move_up(void)
{
	int		i;
	t_arg	*tmp;
	int		cols;

	i = 0;
	tmp = *g_select.active_arg;
	cols = count_columns();
	while (++i < cols)
		tmp = tmp->prev;
	g_select.active_arg = &tmp->prev;
}

/*
** Moves down the argument list
**
** @param		N/A
** @return		N/A
*/

static void	move_down(void)
{
	int		i;
	t_arg	*tmp;
	int		cols;

	i = 0;
	tmp = *g_select.active_arg;
	cols = count_columns();
	while (++i < cols)
		tmp = tmp->next;
	g_select.active_arg = &tmp->next;
}

/*
** Provides argument browsing capabilities using the arrow keys
**
** @param		direction		the direction in which to go
** @return		N/A
*/

void		move(t_dir direction)
{
	t_arg		*active;

	active = *g_select.active_arg;
	if (direction == RIGHT_DIR)
		g_select.active_arg = &active->next;
	else if (direction == LEFT_DIR)
		g_select.active_arg = &active->prev;
	else if (direction == UP_DIR)
		move_up();
	else if (direction == DOWN_DIR)
		move_down();
}



/*
** Returns either the current width or height of the terminal depending on the
** value of 'w_or_h'
**
** @param     w_or_h    1 for width, 0 for height
** @return    The value of the width/height
*/

static int	get_term_size(int w_or_h)
{
	struct winsize	w;

	ioctl(STDERR_FILENO, TIOCGWINSZ, &w);
	return ((w_or_h) ? w.ws_col : w.ws_row);
}

/*
** Counts the maximum amount of columns possible on the current terminal size
**
** @param     N/A
** @return    The total amount of columns possible
*/

int			count_columns(void)
{
	int cols;

	cols = get_term_size(1) / (count_max_arg_len() + 1);
	if (!cols)
		cols = 1;
	if ((count_max_arg_len() + 1) * g_select.argc < get_term_size(1))
		cols = g_select.argc;
	return (cols);
}

/*
** Prints the value of the passed in argument in the desired fd
**
** Depending on the type of the argument, we print it in a specific color
** and then set it back to the default color.
**
** @param     arg     The argument to print the value of
** @param     fd      The file descriptor in which to print to
** @return    N/A
*/

void		print_value_fd(t_arg *arg, int fd)
{
	if (arg->type == C_T && fd == STDERR_FILENO)
		ft_putstr_fd(C_COLOR, fd);
	else if (arg->type == O_T && fd == STDERR_FILENO)
		ft_putstr_fd(O_COLOR, fd);
	else if (arg->type == H_T && fd == STDERR_FILENO)
		ft_putstr_fd(H_COLOR, fd);
	else if (arg->type == MAKEFILE_T && fd == STDERR_FILENO)
		ft_putstr_fd(MAKEFILE_COLOR, fd);
	else if (arg->type == DOT_T && fd == STDERR_FILENO)
		ft_putstr_fd(DOT_COLOR, fd);
	else if (arg->type == A_T && fd == STDERR_FILENO)
		ft_putstr_fd(A_COLOR, fd);
	ft_putstr_fd(arg->value, fd);
	if (fd == STDERR_FILENO)
		ft_putstr_fd(DEFAULT_COLOR, fd);
}

/*
** Displays the list of arguments on the screen
**
** Depending on the type of the value and the state in which it is, it will:
** - underline the text if it's the active value
** - reverse video the text if the value is selected
** and then it prints the value
**
** @param     args    The list of arguments
** @param     first   The first element of the list, passed as an argument to
**                    save lines in the function (25 lines limit)
** @param     rows    The amount of rows possible
** @param     cols    The amount of columns possible
** @return    N/A
*/

static void	display_args(t_arg *args, t_arg *first, int rows, int cols)
{
	int		i;
	int		j;
	int		str_len;

	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
		{
			if (args == (*g_select.active_arg))
				ft_putstr_fd(UNDERLINED, STDERR_FILENO);
			if (args->is_selected)
				ft_putstr_fd(REVERSE_VIDEO_COLOR, STDERR_FILENO);
			print_value_fd(args, STDERR_FILENO);
			str_len = ft_strlen(args->value);
			while (str_len++ <= count_max_arg_len())
				ft_putstr_fd(" ", STDERR_FILENO);
			if (args->next == first)
				break ;
			args = args->next;
		}
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

/*
** Displays the columns of values
**
** If it cannot fit at least 1 column on the screen, it displays
** a blank screen
** If it can, it first clears the whole screen using the "cl" id of the
** terminfo database, calculates rows and columns.
** It also displays a blank screen if the height of the window is not long
** enough. Then it displays thre list of arguments.
**
** @param     N/A
** @return    N/A
*/


int		count_max_arg_len(void)
{
	int		max;
	int		curr_len;
	t_arg	*first;
	t_arg	*tmp;

	if (!g_select.args || !g_select.args->value)
		return (0);
	max = 0;
	tmp = g_select.args;
	first = tmp;
	while (tmp)
	{
		curr_len = ft_strlen(tmp->value);
		if (curr_len > max)
			max = curr_len;
		if (tmp->next == first)
			break ;
		tmp = tmp->next;
	}
	return (max);
}

void		column_display(void)
{
	int		cols;
	int		rows;

	if (!g_select.args || count_max_arg_len() > get_term_size(1))
		return ;
	tputs(tgetstr("cl", NULL), 1, ft_printnbr);
	cols = count_columns();
	rows = g_select.argc / cols;
	if (rows > get_term_size(0))
		return ;
	if (g_select.argc % cols)
		++rows;
	display_args(g_select.args, g_select.args, rows, cols);
}

void	reset_default_conf(void)
{
	tcsetattr(STDERR_FILENO, TCSANOW, &g_select.old_attr);
	tputs(tgetstr("ve", NULL), 1, ft_printnbr);
	tputs(tgetstr("te", NULL), 1, ft_printnbr);
}



static int	ft_max_arglen(void)
{
	int i;
	int max;

	i = 0;
	max = 0;
	while (g_sel.args[i])
	{
		if ((int)ft_strlen(g_sel.args[i]) > max)
			max = (int)ft_strlen(g_sel.args[i]);
		i++;
	}
	return (max);
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