/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 10:18:38 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/20 12:34:22 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	give_cmd_inprogress(t_historic *termcaps, char **entry)
{
	if (termcaps->cmd_inprogress != NULL)
	{
		*entry = s_strdup(termcaps->cmd_inprogress, __FILE__);
		ft_putstr(*entry);
		termcaps->cur_x = ft_strlen(*entry);
	}
	else
	{
		*entry = NULL;
		termcaps->cur_x = 0;
	}
	termcaps->hist = 0;
}

int			ft_key_down(t_historic *tcaps, char **entry)
{
	int		col_sup;

	if (tcaps->hist == 0 || tcaps->cur == NULL || tcaps->select_mode == 1)
		return (1);
	col_sup = (tcaps->cur_x + tcaps->len_prompt) / tcaps->ws.ws_col;
	if (*entry != NULL)
		free(*entry);
	erase_cmd(col_sup, tcaps);
	if (tcaps->cur == tcaps->end)
		give_cmd_inprogress(tcaps, entry);
	else if (tcaps->cur != tcaps->end)
	{
		tcaps->cur = tcaps->cur->next;
		*entry = s_strdup(tcaps->cur->content, __FILE__);
		ft_putstr(*entry);
		tcaps->cur_x = ft_strlen(*entry);
		if (tcaps->cur_x == (int)ft_strlen(*entry) &&
					(tcaps->cur_x + tcaps->len_prompt) % tcaps->ws.ws_col == 0)
			tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
	}
	return (1);
}
