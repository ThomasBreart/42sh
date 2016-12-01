/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_still_open.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 01:54:32 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/18 01:55:51 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	del_backslash_end(char **entry)
{
	char	*tmp;

	tmp = s_strndup(*entry, ft_strlen(*entry) - 1, __FILE__);
	ft_strdel(entry);
	*entry = tmp;
}

static void	update_entry(t_historic *termcaps, char **entry, int end_backslash)
{
	char	*tmp;

	if (end_backslash == 1)
		del_backslash_end(entry);
	if (termcaps->bslash_split == NULL)
		termcaps->bslash_split = s_strdup(*entry, __FILE__);
	else
	{
		tmp = s_strjoin(termcaps->bslash_split, *entry, __FILE__);
		free(termcaps->bslash_split);
		termcaps->bslash_split = tmp;
	}
	ft_memdel((void**)entry);
	ft_memdel((void**)&termcaps->cmd_inprogress);
	tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
	termcaps->len_prompt = ft_strlen(termcaps->prompt_open);
	termcaps->prompt_current = termcaps->prompt_open;
	ft_putstr(termcaps->prompt_current);
	termcaps->cur_x = 0;
}

int			cmd_still_open(t_historic *termcaps, char **entry)
{
	int		ret;
	char	*full_cmd;
	int		end_backslash;

	end_backslash = 0;
	ret = 1;
	if (*entry == NULL)
	{
		tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
		ft_putstr(termcaps->prompt_current);
		return (1);
	}
	full_cmd = find_full_cmd(*entry, termcaps);
	if ((ret = cmd_is_open(full_cmd, &end_backslash)) == 1)
	{
		update_entry(termcaps, entry, end_backslash);
		free(full_cmd);
		return (1);
	}
	free(full_cmd);
	termcaps->len_prompt = ft_strlen(termcaps->prompt);
	return (ret);
}
