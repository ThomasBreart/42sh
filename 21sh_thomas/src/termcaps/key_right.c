/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_right.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 23:01:25 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/27 17:48:18 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_key_right(t_historic *tcaps, char **entry)
{
	if (*entry != NULL && tcaps->cur_x < (int)ft_strlen(*entry))
	{
		if ((tcaps->cur_x + tcaps->len_prompt + 1) % tcaps->ws.ws_col == 0)
			tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
		else
			tputs(tgoto(tgetstr("nd", NULL), 0, 0), 1, ft_outc);
		tcaps->cur_x++;
		if (tcaps->select_mode == 1)
			show_entry(tcaps, *entry);
	}
	return (1);
}
