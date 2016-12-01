/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sigcont.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 01:57:24 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 02:08:56 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	handler_sigcont(int numsig)
{
	t_historic	*termcaps;
	t_save_fd	*save;

	signal(SIGTSTP, handler_sigtstp);
	termcaps = get_termcaps();
	numsig = 42;
	save = get_set_save_fd(NULL);
	if (termcaps->istty == 1 && set_termios(&termcaps->term, save) == -1)
		internal_error("handler_sigcont", "set_termcaps", 1);
	ft_putstr(termcaps->prompt);
	(void)numsig;
}
