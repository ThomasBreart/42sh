/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_selection_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 00:29:03 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/27 18:49:57 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	set_end_select(t_historic *termcaps)
{
	int		tmp;

	if (termcaps->cur_x < termcaps->start_select)
	{
		tmp = termcaps->start_select;
		termcaps->start_select = termcaps->cur_x;
		termcaps->end_select = tmp;
	}
	else
		termcaps->end_select = termcaps->cur_x;
}

int		ft_key_selection_mode(t_historic *termcaps, char **entry)
{
	if (*entry == NULL)
		return (1);
	if (termcaps->select_mode == 0)
	{
		termcaps->select_mode = 1;
		termcaps->start_select = termcaps->cur_x;
		termcaps->end_select = -1;
	}
	else
	{
		termcaps->select_mode = 0;
		termcaps->start_select = -1;
		termcaps->end_select = -1;
		show_entry(termcaps, *entry);
	}
	return (1);
}
