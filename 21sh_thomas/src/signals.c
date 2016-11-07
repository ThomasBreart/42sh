/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/22 02:40:41 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/07 19:03:35 by mfamilar         ###   ########.fr       */
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

static void	handler_sigint(int numsig)
{
	t_historic *termcaps;

	numsig = 42;
	termcaps = get_termcaps();
	if (termcaps->istty == 0)
		exit(0);
	if (termcaps->in_read == 1)
		ft_putchar_fd(EOF, STDIN_FILENO);
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

void		resize_win(int numsig)
{
	t_historic *termcaps;

	termcaps = get_termcaps();
	ioctl(0, TIOCGWINSZ, &termcaps->ws);
	if (termcaps->in_getcmd == 1)
		show_entry(termcaps, *termcaps->entry);
	(void)numsig;
}

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
}

static void	handler_sigcont(int numsig)
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
	signal(SIGTSTP, handler_sigtstp);
	signal(SIGINT, handler_sigint);
	signal(SIGCONT, handler_sigcont);
	signal(SIGCHLD, SIG_DFL);
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
