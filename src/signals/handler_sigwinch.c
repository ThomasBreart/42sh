/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sigwinch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 01:56:19 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 02:10:41 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void		handler_sigwinch(int numsig)
{
	t_historic	*termcaps;
	int			offset;

	termcaps = get_termcaps();
	ioctl(0, TIOCGWINSZ, &termcaps->ws);
	if (termcaps->in_explorer)
	{
		offset = recalc_need_size(NULL, NULL);
		if (offset > termcaps->ws.ws_col || termcaps->ws.ws_row <= 3)
			write(1, "\033c", 2);
		if (offset > termcaps->ws.ws_col)
		{
			write(1, "Bad size: ", 10);
			ft_putnbr_fd(offset, 2);
			write(1, " columns needed\n", 15);
		}
		if (termcaps->ws.ws_row <= 3)
			write(1, "Bad size: more row needed\n", 25);
	}
	if (termcaps->in_getcmd == 1)
		show_entry(termcaps, *termcaps->entry);
	(void)numsig;
}
