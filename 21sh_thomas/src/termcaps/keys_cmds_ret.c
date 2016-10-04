/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_cmds_ret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/21 07:49:26 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/27 18:34:18 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	cmd_still_open(t_historic *termcaps, char **entry)
{
	int		ret;

	ret = 1;
	if (check_backslash(termcaps, *entry) == 1 ||
		(ret = check_open_chars(termcaps, *entry, '(', ')')) != 0 ||
		(ret = check_open_chars(termcaps, *entry, '[', ']')) != 0 ||
		(ret = check_open_chars(termcaps, *entry, '{', '}')) != 0 ||
		(ret = check_open_quotes(termcaps, *entry)) != 0)
	{
		if (ret == -1)
			return (-1);
		ft_memdel((void**)entry);
		ft_memdel((void**)&termcaps->cmd_inprogress);
		tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
		termcaps->len_prompt = ft_strlen(termcaps->prompt_open);
		termcaps->prompt_current = termcaps->prompt_open;
		ft_putstr(termcaps->prompt_current);
		termcaps->cur_x = 0;
		return (1);
	}
	termcaps->len_prompt = ft_strlen(termcaps->prompt);
	return (0);
}

static void	concat_bslash_split(t_historic *termcaps, char **entry)
{
	char	*tmp;

	if (termcaps->bslash_split != NULL && *entry != NULL)
	{
		tmp = s_strjoin(termcaps->bslash_split, *entry, __FILE__);
		free(*entry);
		*entry = tmp;
		free(termcaps->bslash_split);
		termcaps->bslash_split = NULL;
	}
	else if (termcaps->bslash_split != NULL && *entry == NULL)
		*entry = termcaps->bslash_split;
}

static int	empty_entry(t_historic *termcaps, char **entry)
{
	ft_memdel((void**)entry);
	if (termcaps->bslash_split != NULL)
	{
		*entry = s_strdup(termcaps->bslash_split, __FILE__);
		add_historic(termcaps, entry, 1);
		return (0);
	}
	termcaps->cur_x = 0;
	ft_memdel((void**)&termcaps->cmd_inprogress);
	ft_putstr(termcaps->prompt_current);
	return (-1);
}

/*
**	ret = 0 -> comportement normal, prepare la cmd a etre execute
**	ret = 1 -> ya un bslash
**	ret = -1 -> la cmd est a une erreurs de parsing, elle a un ou
**				plusieurs parentheses / quotes en trop / ou elle est vide
*/

int			ft_key_ret(t_historic *termcaps, char **entry)
{
	int		ret;

	ret = -1;
	if (termcaps->select_mode == 1)
		return (1);
	if (termcaps->in_llr == 1)
		return (ft_key_ret_llr(termcaps, entry));
	if ((ret = cmd_still_open(termcaps, entry)) == 1)
		return (1);
	termcaps->len_prompt = ft_strlen(termcaps->prompt);
	termcaps->prompt_current = termcaps->prompt;
	set_cur_end(termcaps, *entry);
	if (ret != -1)
		tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
	termcaps->cur_x = 0;
	if (*entry == NULL || is_just_spaces(*entry) != 0)
		return (empty_entry(termcaps, entry));
	concat_bslash_split(termcaps, entry);
	add_historic(termcaps, entry, 1);
	ft_memdel((void**)&termcaps->cmd_inprogress);
	if (ret == -1)
		ft_memdel((void**)entry);
	return (ret);
}
