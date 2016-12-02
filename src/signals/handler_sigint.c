/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sigint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 01:55:53 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/01 17:10:01 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void		sigint_getcmd(t_historic *termcaps)
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

void			handler_sigint(int numsig)
{
	t_historic *termcaps;

	termcaps = get_termcaps();
	if (termcaps->istty == 0)
		exit(0);
	if ((termcaps->in_read == 1) ||
			(termcaps->in_llr == 1 && termcaps->in_getcmd == 1))
		close(STDIN_FILENO);
	else if (termcaps->in_getcmd == 1)
		sigint_getcmd(termcaps);
	ft_putchar('\n');
	if (termcaps->in_child == 0 && termcaps->in_llr == 0 &&
						termcaps->in_builtin == 0 && termcaps->wordnofork == 0)
	{
		ft_putstr(termcaps->prompt);
		termcaps->prompt_current = termcaps->prompt;
	}
	(void)numsig;
}
