/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 23:04:54 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/27 16:23:19 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	Gestion de l'historique : reaffiche la commande precedente
**	termcaps->hist == 1 -> on est dans l historique / == 0 -> cmd en cours
*/

int		ft_key_up(t_historic *termcaps, char **entry)
{
	int		col_sup;

	if (termcaps->select_mode == 1)
		return (1);
	if (termcaps->cur != NULL && termcaps->hist == 0)
		termcaps->hist = 1;
	else if (termcaps->cur != NULL && termcaps->cur != termcaps->head)
		termcaps->cur = termcaps->cur->prev;
	if (termcaps->cur != NULL)
	{
		col_sup = (termcaps->cur_x + termcaps->len_prompt) /
														termcaps->ws.ws_col;
		if (*entry != NULL)
			free(*entry);
		erase_cmd(col_sup, termcaps);
		*entry = s_strdup(termcaps->cur->content, __FILE__);
		ft_putstr(*entry);
		termcaps->cur_x = ft_strlen(*entry);
		if (termcaps->cur_x == (int)ft_strlen(*entry) &&
						(termcaps->cur_x + termcaps->len_prompt) %
													termcaps->ws.ws_col == 0)
			tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
	}
	return (1);
}
