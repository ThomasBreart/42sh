/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 18:42:40 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 05:54:34 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_key_eof(t_historic *termcaps, char **entry)
{
	if (termcaps->select_mode == 1)
		return (1);
	if (termcaps->in_llr == 1)
	{
		if (*entry == NULL)
		{
			termcaps->llr_eof = 1;
			return (0);
		}
		else
			return (1);
	}
	if (*entry == NULL && termcaps->bslash_split == NULL)
		builtin_exit(NULL, NULL, NULL);
	else if (*entry == NULL)
	{
		ft_putendl_fd("42sh: syntax error: unexpected end of file",
																STDERR_FILENO);
		add_historic(termcaps, &termcaps->bslash_split, 1, 1);
		ft_strdel(&termcaps->bslash_split);
		termcaps->prompt_current = termcaps->prompt;
		termcaps->len_prompt = ft_strlen(termcaps->prompt_current);
		ft_putstr(termcaps->prompt_current);
	}
	else
		ft_key_supp(termcaps, entry);
	return (1);
}
