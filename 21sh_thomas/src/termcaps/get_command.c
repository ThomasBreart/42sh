/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/10 11:50:17 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/27 07:16:08 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	find_key(long int r, t_func_tab *funcs)
{
	int		i;

	i = 0;
	while (r != funcs[i].k)
	{
		if (funcs[i].k == KEY_NOPE)
			break ;
		i++;
	}
	return (i);
}

static int	exec_key(t_func_tab *funcs, int x, t_historic *tcaps, char **entry)
{
	int		ret;

	if (funcs[x].k != KEY_NOPE)
		ret = (funcs[x].f)(tcaps, entry);
	else
	{
		ret = cmd_add_char(tcaps, entry);
	}
	return (ret);
}

int			get_command(t_historic *termcaps, char **entry)
{
	long int	r;
	int			x;
	t_func_tab	*funcs;
	int			d;

	init_var_cmd(termcaps, entry);
	funcs = get_func_tab();
	r = 0;
	while ((d = read(STDIN_FILENO, &r, sizeof(long int))))
	{
		termcaps->buff = r;
		x = find_key(r, funcs);
		if (exec_key(funcs, x, termcaps, entry) == 0)
			return (1);
		r = 0;
	}
	return (0);
}
