/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 18:42:40 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/07 19:29:46 by tbreart          ###   ########.fr       */
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
	else
		ft_key_supp(termcaps, entry);
	return (1);
}
