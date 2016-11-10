/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_home.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 00:43:45 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/27 18:04:10 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_key_home(t_historic *termcaps, char **entry)
{
	int		i;

	i = (termcaps->cur_x + termcaps->len_prompt) % termcaps->ws.ws_col;
	while (*entry != NULL && i > 0 && termcaps->cur_x > 0)
	{
		tputs(tgoto(tgetstr("le", NULL), 0, 0), 1, ft_outc);
		termcaps->cur_x--;
		i--;
	}
	if (termcaps->select_mode == 1)
		show_entry(termcaps, *entry);
	return (1);
}
