/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:15:33 by jbrigett          #+#    #+#             */
/*   Updated: 2020/08/17 16:15:34 by jbrigett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	The getenv() function searches the environment list to find the
**	environment variable name, and returns a pointer to the corresponding
**	value string.
**	The getenv() function returns a pointer to the value in the
**	environment, or NULL if there is no match.
**
**	int tgetent (char *buffer, char *termtype);
**	The argument termtype is a string which is the name for the type of terminal
**	to look up. Usually you would obtain this from the environment
**	variable TERM using getenv ("TERM").
**	If you are using the GNU version of termcap, you can alternatively ask
**	tgetent to allocate enough space. Pass a null pointer for buffer, and tgetent
**	itself allocates the storage using malloc. There is no way to get the address
**	that was allocated, and you shouldn't try to free the storage.
**	The return value of tgetent is -1 if there is some difficulty accessing
**	the data base of terminal types, 0 if the data base is accessible but the
**	specified type is not defined in it, and some other value otherwise.
**
**	The isatty() function shall test whether fildes,
**	an open file descriptor, is associated with a terminal device.
*/
void	sl_errors(int argc, char **argv, char **env)
{
	if (argc == 1)
	{
		ft_dprintf(2, "Usage: %s arg1 [arg2...]\n", argv[0]);
		exit(0);
	}
	if (!env[0] || !getenv("TERM"))
	{
		ft_dprintf(2, "Specify a terminal type with 'setenv TERM <yourtype>'.\n");
		exit(0);
	}
	if (tgetent(NULL, getenv("TERM")) == 0)
	{
		ft_dprintf(2, "Terminal type `%s' is not defined.\n", getenv("TERM"));
		exit(0);
	}
	if (tgetent(NULL, getenv("TERM")) < 0)
	{
		ft_dprintf(2, "Could not access the termcap data base.\n");
		exit(0);
	}
}