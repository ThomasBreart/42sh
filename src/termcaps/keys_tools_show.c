/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_tools_show.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 00:01:45 by tbreart           #+#    #+#             */
/*   Updated: 2016/08/14 16:24:12 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void		show_entry_select_mode(t_historic *termcaps, char *entry)
{
	int		i;

	i = 0;
	while (entry[i] != '\0' &&
			(i < termcaps->start_select && i < termcaps->cur_x))
	{
		ft_putchar(entry[i]);
		++i;
	}
	while (entry[i] != '\0' &&
						(i < termcaps->start_select || i < termcaps->cur_x))
	{
		tputs(tgoto(tgetstr("mr", NULL), 0, 0), 1, ft_outc);
		ft_putchar(entry[i]);
		++i;
	}
	tputs(tgoto(tgetstr("me", NULL), 0, 0), 1, ft_outc);
	while (entry[i] != '\0')
	{
		ft_putchar(entry[i]);
		++i;
	}
}

void			show_entry(t_historic *termcaps, char *entry)
{
	int		col_sup;
	int		decal;

	col_sup = (termcaps->cur_x + termcaps->len_prompt) / termcaps->ws.ws_col;
	erase_cmd(col_sup, termcaps);
	if (entry != NULL)
	{
		if (termcaps->select_mode == 1)
			show_entry_select_mode(termcaps, entry);
		else
			ft_putstr(entry);
		decal = ft_strlen(entry) - termcaps->cur_x;
		reset_curx(decal);
	}
}

void			reset_curx(int decal)
{
	while (decal > 0)
	{
		tputs(tgoto(tgetstr("le", NULL), 0, 0), 1, ft_outc);
		decal--;
	}
}

void			erase_cmd(int col_sup, t_historic *termcaps)
{
	if ((termcaps->cur_x + termcaps->len_prompt) % termcaps->ws.ws_col == 0
												&& termcaps->select_mode != 1)
		col_sup--;
	while (col_sup > 0)
	{
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 1, ft_outc);
		col_sup--;
	}
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_outc);
	tputs(tgoto(tgetstr("cd", NULL), 0, 0), 1, ft_outc);
	ft_putstr(termcaps->prompt_current);
}
