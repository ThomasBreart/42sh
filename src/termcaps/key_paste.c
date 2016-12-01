/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_paste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 03:41:43 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/27 16:20:37 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	copy_before_cur(char **entry, t_historic *tcaps, char *tmp, int *k)
{
	int		i;
	char	*tmp2;

	tmp2 = *entry;
	i = 0;
	while (*entry != NULL && i < tcaps->cur_x)
	{
		tmp[i] = tmp2[i];
		i++;
	}
	*k = i;
	return (i);
}

static int	copy_paste(t_historic *termcaps, char *tmp, int i)
{
	int		j;

	j = 0;
	while (termcaps->buff_paste[j] != '\0')
	{
		tmp[i] = termcaps->buff_paste[j];
		j++;
		i++;
	}
	return (i);
}

static int	copy_after_cur(char **entry, char *tmp, int i, int k)
{
	char	*tmp2;
	int		j;

	tmp2 = *entry;
	j = 0;
	while (*entry != NULL && tmp2[k] != '\0')
	{
		tmp[i] = tmp2[k];
		ft_putchar(tmp[i]);
		k++;
		i++;
		j++;
	}
	return (j);
}

/*
**	sorte de concat_entry + show_entry
*/

int			ft_key_paste(t_historic *termcaps, char **entry)
{
	char	*tmp;
	int		i;
	int		k;

	if (termcaps->buff_paste == NULL || termcaps->select_mode == 1)
		return (1);
	ft_putstr(termcaps->buff_paste);
	if (*entry == NULL)
		tmp = s_strnew(ft_strlen(termcaps->buff_paste), __FILE__);
	else
		tmp = s_strnew(ft_strlen(*entry) + ft_strlen(termcaps->buff_paste),
																	__FILE__);
	i = copy_before_cur(entry, termcaps, tmp, &k);
	i = copy_paste(termcaps, tmp, i);
	i = copy_after_cur(entry, tmp, i, k);
	ft_memdel((void**)entry);
	*entry = tmp;
	ft_memdel((void**)&termcaps->cmd_inprogress);
	termcaps->cmd_inprogress = s_strdup(*entry, __FILE__);
	termcaps->cur_x = termcaps->cur_x + ft_strlen(termcaps->buff_paste);
	reset_curx(i);
	if (termcaps->cur_x == (int)ft_strlen(*entry) &&
		(termcaps->cur_x + termcaps->len_prompt) % termcaps->ws.ws_col == 0)
		tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
	return (1);
}
