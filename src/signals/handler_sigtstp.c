/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sigtstp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 01:56:54 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 01:57:04 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	handler_sigtstp(int numsig)
{
	t_historic	*termcaps;
	t_save_fd	*save;
	pid_t		pid;

	numsig = 42;
	termcaps = get_termcaps();
	save = get_set_save_fd(NULL);
	if (termcaps->istty == 1 && set_termios(&termcaps->save, save) == -1)
		internal_error("handler_sigcont", "set_termcaps", 1);
	signal(SIGTSTP, SIG_DFL);
	pid = getpid();
	kill(pid, SIGTSTP);
	(void)numsig;
}
