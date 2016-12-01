/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_cmds_ret_llr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 12:06:36 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/14 12:06:52 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		ft_key_ret_llr(t_historic *termcaps, char **entry)
{
	set_cur_end(termcaps, *entry);
	tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
	termcaps->cur_x = 0;
	return (0);
}
