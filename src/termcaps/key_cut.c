/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_cut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 03:36:20 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/27 19:05:13 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	edit_entry_without_selected_area(t_historic *termcaps, char **entry)
{
	char	*before;
	char	*after;

	before = s_strsub(*entry, 0, termcaps->start_select, __FILE__);
	after = s_strsub(*entry, termcaps->end_select, ft_strlen(*entry), __FILE__);
	free(*entry);
	*entry = s_strjoin(before, after, __FILE__);
	free(before);
	free(after);
}

static int	ft_cut_select_mode(t_historic *termcaps, char **entry)
{
	termcaps->select_mode = 0;
	if (*entry == NULL || termcaps->start_select == termcaps->cur_x)
		return (1);
	ft_strdel(&termcaps->buff_paste);
	set_end_select(termcaps);
	termcaps->buff_paste = s_strsub(*entry, termcaps->start_select,
					(termcaps->end_select - termcaps->start_select), __FILE__);
	edit_entry_without_selected_area(termcaps, entry);
	termcaps->cur_x = termcaps->start_select;
	show_entry(termcaps, *entry);
	return (1);
}

int			ft_key_cut_all(t_historic *termcaps, char **entry)
{
	int		col_sup;

	if (*entry == NULL)
		return (1);
	if (termcaps->select_mode == 1)
		return (ft_cut_select_mode(termcaps, entry));
	if (termcaps->buff_paste != NULL)
		free(termcaps->buff_paste);
	termcaps->buff_paste = *entry;
	*entry = NULL;
	col_sup = (termcaps->cur_x + termcaps->len_prompt) / termcaps->ws.ws_col;
	if (*entry != NULL && termcaps->cur_x == (int)ft_strlen(*entry) &&
		(termcaps->cur_x + termcaps->len_prompt) % termcaps->ws.ws_col == 0)
		col_sup++;
	erase_cmd(col_sup, termcaps);
	termcaps->cur_x = 0;
	return (1);
}

int			ft_key_cut_part(t_historic *termcaps, char **entry)
{
	char*tmp;

	if (*entry == NULL || termcaps->cur_x == (int)ft_strlen(*entry))
		return (1);
	if (termcaps->select_mode == 1)
		return (ft_cut_select_mode(termcaps, entry));
	if (termcaps->buff_paste != NULL)
		free(termcaps->buff_paste);
	termcaps->buff_paste = s_strsub(*entry, termcaps->cur_x,
							(ft_strlen(*entry) - termcaps->cur_x), __FILE__);
	tmp = s_strsub(*entry, 0, termcaps->cur_x, __FILE__);
	free(*entry);
	*entry = tmp;
	tputs(tgoto(tgetstr("cd", NULL), 0, 0), 1, ft_outc);
	return (1);
}
