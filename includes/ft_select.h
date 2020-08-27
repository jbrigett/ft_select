/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 19:04:03 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/17 18:38:22 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <termcap.h>
# include <termios.h>
# include <curses.h>
# include <stdlib.h>
# include <unistd.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <fcntl.h>
# include "ft_printf.h"

/*	An ANSI escape sequence has the format `ESC[X;Ym', where `ESC' is
**	the escape character (octal 033). `X' and, optionally, `Y', is one of
**	the following escape codes:
**	CT - type .c
**	OT - type .o
**	HT - type .h
**	MT - Makefile
**	AT - type .a
**	DT - start w/ .
**	ST - col by default
**	RV - reverse video color
**	UN - underlined text
*/
# define ST_COL		"\033[0m"
# define UN_COL		"\033[4m"
# define RV_COL		"\033[7m"
# define AT_COL		"\033[31m"
# define DT_COL		"\033[32m"
# define MT_COL		"\033[33m"
# define HT_COL		"\033[34m"
# define CT_COL		"\033[35m"
# define OT_COL		"\033[36m"

# define ENTER_K	0xA
# define ESC_K		0x1B
# define SPACEBAR	0x20
# define A_K		65
# define Z_K		90
# define BACKSPACE	0x7F
# define LEFT_K		0x445B1B
# define UP_K		0x415B1B
# define RIGHT_K	0x435B1B
# define DOWN_K		0x425B1B
# define DELETE_K	0x7E335B1B

/*
** Type is int type arg to make different colors
** for different files' types(part of bonus):
** 0 - .c
** 1 - .o
** 2 - .h
** 3 - .a
** 4 - Makefile
** 5 - files start w/ '.'s
** 6 - other type
*/
typedef struct		s_args
{
	struct s_args	*prev;
	struct s_args	*next;
	char			*value;
	int8_t			select;
	int8_t			type;
}					t_args;

typedef struct		s_select
{
	struct termios	old_attr;
	struct termios	new_attr;
	t_args			*arg;
	t_args			*cur;
	int				argc;
	int				amount;
	int				rows;
	int				cols;
	int				fd;
}					t_select;

/*
** Checking terminal info and saving current attributes
*/
void				sl_errors(int argc, char **argv, char **env);
void				sl_init(t_select *sl, int argc, char **argv);
void				sl_restore(t_select *sl);

/*
** Signals handler
*/
void				sl_signals(t_select	*sl);
t_select			*get_t_select(t_select **t);
void				signal_handler(int s);
void				sl_resize(int s);
void				sl_restart(int s);
void				sl_suspend(int s);

/*
** Printing args
*/
int					get_size(int flag);
int					get_max_len(t_select *sl);
void				print_args(t_args *first, t_select *sl);
void				print_color(t_args *arg);
int					get_cols(t_select *sl);
void				sl_print(t_select *sl);
void				sl_quit(int s);

/*
** Move between args
*/
void				move_down(t_select *sl);
void				move_up(t_select *sl);
/*
** Initialization list of arguments
*/
void				new_arg(t_select *sl, char *value);
void				set_type(t_args *sl, char *value);
int8_t				sl_check_extention(char *value, const char *ext);
void				delete_arg(t_select *sl);
void				free_args(t_select *sl);

/*
** Key pressed
*/
void				on_key_pressed(t_select *sl);
int					ft_putc(int c);

#endif
