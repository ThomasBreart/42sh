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

#include "ft_21sh.h"

void		handler_sigwinch(int numsig)
{
	t_historic *termcaps;

	termcaps = get_termcaps();
	ioctl(0, TIOCGWINSZ, &termcaps->ws);
	if (termcaps->in_getcmd == 1)
		show_entry(termcaps, *termcaps->entry);
	(void)numsig;
}
