/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 00:54:54 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/10 18:28:50 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	show_entry_del(t_historic *tcaps, char *entry)
{
	int		col_sup;
	int		decal;

	col_sup = (tcaps->cur_x + tcaps->len_prompt) / tcaps->ws.ws_col;
	if (((tcaps->cur_x + tcaps->len_prompt + 1) % tcaps->ws.ws_col) == 0)
		col_sup++;
	erase_cmd(col_sup, tcaps);
	if (entry != NULL)
	{
		ft_putstr(entry);
		if (((tcaps->cur_x + tcaps->len_prompt) % tcaps->ws.ws_col) == 0)
			if (tcaps->cur_x == (int)ft_strlen(entry))
				tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
		decal = ft_strlen(entry) - (tcaps->cur_x);
		reset_curx(decal);
	}
}

static int	remove_one_char_del(char **entry, int cur_x)
{
	char	*new;
	int		i;

	if ((i = ft_strlen(*entry)) == 1)
	{
		free(*entry);
		*entry = NULL;
		return (1);
	}
	new = s_strnew(i - 1, __FILE__);
	i = 0;
	while (i < (cur_x - 1))
	{
		new[i] = (*entry)[i];
		i++;
	}
	if ((*entry)[i++] != '\0')
		while ((*entry)[i] != '\0')
		{
			new[i - 1] = (*entry)[i];
			i++;
		}
	free(*entry);
	*entry = new;
	return (1);
}

int			ft_key_del(t_historic *termcaps, char **entry)
{
	if (*entry == NULL || termcaps->select_mode == 1)
		return (1);
	if (termcaps->cur_x > 0)
	{
		remove_one_char_del(entry, termcaps->cur_x);
		termcaps->cur_x--;
	}
	if (termcaps->hist == 1)
	{
		ft_strdel(&termcaps->cur->content);
		termcaps->cur->content = s_strdup(*entry, __FILE__);
		termcaps->cur->content_modified = 1;
	}
	ft_strdel(&termcaps->cmd_inprogress);
	if (*entry != NULL)
		termcaps->cmd_inprogress = s_strdup(*entry, __FILE__);
	show_entry_del(termcaps, *entry);
	return (1);
}
