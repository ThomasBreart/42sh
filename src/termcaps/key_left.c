/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_left.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 22:56:41 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/27 08:12:55 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	Deplace le curseur vers la gauche.
**	Si la commande est sur plusieurs lignes et qu'il doit remonter : fait
**	remonter le curseur verticalement et le decale vers la droite jusqu a
**	la fin de la ligne
*/

int		ft_key_left(t_historic *tcaps, char **entry)
{
	int		i;

	if (tcaps->cur_x > 0)
	{
		if (*entry != NULL && tcaps->cur_x == (int)ft_strlen(*entry) &&
					(tcaps->cur_x + tcaps->len_prompt) % tcaps->ws.ws_col == 0)
		{
			i = 0;
			tputs(tgoto(tgetstr("up", NULL), 0, 0), 1, ft_outc);
			while (i < tcaps->ws.ws_col)
			{
				tputs(tgoto(tgetstr("nd", NULL), 0, 0), 1, ft_outc);
				i++;
			}
		}
		else
			tputs(tgoto(tgetstr("le", NULL), 0, 0), 1, ft_outc);
		tcaps->cur_x--;
		if (tcaps->select_mode == 1)
			show_entry(tcaps, *entry);
	}
	return (1);
}
