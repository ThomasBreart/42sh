/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/22 02:40:41 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/03 18:37:07 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int			sig_child_func(int status)
{
	t_historic	*termcaps;

	if (WEXITSTATUS(status) == EXIT_FAILURE)
		return (-1);
	termcaps = get_termcaps();
	if (WTERMSIG(status) == SIGCHLD)
		return (1);
	if (WTERMSIG(status) == SIGSEGV)
		ft_putendl_fd("Child - Segmentation fault", STDERR_FILENO);
	return (-1);
}

void		signals_management(void)
{
	int		i;

	i = 1;
	while (i <= 31)
	{
		signal(i, SIG_IGN);
		i++;
	}
	signal(SIGSEGV, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGTSTP, handler_sigtstp);
	signal(SIGINT, handler_sigint);
	signal(SIGCONT, handler_sigcont);
	signal(SIGWINCH, handler_sigwinch);
}

void		signals_reset(void)
{
	int		i;

	i = 1;
	while (i <= 31)
	{
		signal(i, SIG_DFL);
		i++;
	}
}
