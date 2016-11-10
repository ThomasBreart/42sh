/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 03:32:05 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/27 18:49:41 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_copy_select_mode(t_historic *termcaps, char **entry)
{
	termcaps->select_mode = 0;
	if (*entry == NULL || termcaps->start_select == termcaps->cur_x)
		return (1);
	ft_strdel(&termcaps->buff_paste);
	set_end_select(termcaps);
	termcaps->buff_paste = s_strsub(*entry, termcaps->start_select,
					(termcaps->end_select - termcaps->start_select), __FILE__);
	show_entry(termcaps, *entry);
	return (1);
}

int		ft_key_copy_all(t_historic *termcaps, char **entry)
{
	if (*entry == NULL)
		return (1);
	if (termcaps->select_mode == 1)
		return (ft_copy_select_mode(termcaps, entry));
	if (termcaps->buff_paste != NULL)
		free(termcaps->buff_paste);
	termcaps->buff_paste = s_strdup(*entry, __FILE__);
	return (1);
}

int		ft_key_copy_part(t_historic *termcaps, char **entry)
{
	if (*entry == NULL || termcaps->cur_x == (int)ft_strlen(*entry))
		return (1);
	if (termcaps->select_mode == 1)
		return (ft_copy_select_mode(termcaps, entry));
	if (termcaps->buff_paste != NULL)
		free(termcaps->buff_paste);
	termcaps->buff_paste = s_strsub(*entry, termcaps->cur_x,
			(ft_strlen(*entry) - termcaps->cur_x), __FILE__);
	return (1);
}
