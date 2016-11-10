/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 20:58:51 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/23 20:58:53 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_outc(int c)
{
	ft_putchar(c);
	return (0);
}

void	set_cur_end(t_historic *termcaps, char *entry)
{
	if (entry == NULL)
		return ;
	while (termcaps->cur_x < (int)ft_strlen(entry))
	{
		if ((termcaps->cur_x + termcaps->len_prompt + 1) %
												termcaps->ws.ws_col == 0)
			tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
		else
			tputs(tgoto(tgetstr("nd", NULL), 0, 0), 1, ft_outc);
		termcaps->cur_x++;
	}
}
