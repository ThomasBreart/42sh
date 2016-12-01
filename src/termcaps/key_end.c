/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 00:53:07 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/27 18:06:04 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		ft_key_end(t_historic *termcaps, char **entry)
{
	int		i;

	i = (termcaps->cur_x + termcaps->len_prompt) % termcaps->ws.ws_col;
	i++;
	while (*entry != NULL && i < termcaps->ws.ws_col &&
						termcaps->cur_x < (int)ft_strlen(*entry))
	{
		tputs(tgoto(tgetstr("nd", NULL), 0, 0), 1, ft_outc);
		termcaps->cur_x++;
		i++;
	}
	if (termcaps->select_mode == 1)
		show_entry(termcaps, *entry);
	return (1);
}
