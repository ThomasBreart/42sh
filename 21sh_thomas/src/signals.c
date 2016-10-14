/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/22 02:40:41 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/14 12:35:30 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			sig_child_func(int status)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if (WTERMSIG(status) == SIGSEGV)
		ft_putendl_fd("Child - Segmentation fault", STDERR_FILENO);
	return (-1);
}

static void	handler(int numsig)
{
	t_historic *termcaps;

	termcaps = get_termcaps();
	if (numsig == SIGINT)
	{
		if (termcaps->in_getcmd == 1)
		{
			ft_memdel((void**)&termcaps->cmd_inprogress);
			ft_memdel((void**)&termcaps->bslash_split);
			if ((*termcaps->entry) != NULL)
			{
				free((*termcaps->entry));
				(*termcaps->entry) = NULL;
				termcaps->cur_x = 0;
				termcaps->hist = 0;
			}
		}
		ft_putchar('\n');
		if (termcaps->in_child == 0 && termcaps->in_llr == 0)
		{
			ft_putstr(termcaps->prompt);
			termcaps->prompt_current = termcaps->prompt;
		}
	}
}

void		resize_win(int numsig)
{
	t_historic *termcaps;

	termcaps = get_termcaps();
	ioctl(0, TIOCGWINSZ, &termcaps->ws);
	if (termcaps->in_getcmd == 1)
		show_entry(termcaps, *termcaps->entry);
	(void)numsig;
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
	// signal(SIGCHLD, SIG_DFL);
	signal(SIGINT, handler);
	signal(SIGWINCH, resize_win);
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
