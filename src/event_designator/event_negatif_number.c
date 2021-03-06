/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_negatif_number.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 17:26:56 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/06 12:24:57 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		is_event_negatif_number(char *str)
{
	++str;
	if (*str == '-')
		++str;
	else
		return (0);
	return (ft_isdigit(*str));
}

int		event_negatif_number(char *sub_cmd, char **new_str)
{
	t_historic	*termcaps;
	int			cmd_number;
	t_list		*cmd_histo;

	termcaps = get_termcaps();
	cmd_number = ft_atoi(sub_cmd + 1);
	cmd_histo = termcaps->end;
	while (cmd_number < 0)
	{
		if (cmd_histo == termcaps->head)
			break ;
		cmd_histo = cmd_histo->prev;
		++cmd_number;
	}
	if (cmd_number < 0)
		return (E_NOT_FOUND);
	*new_str = s_strdup(cmd_histo->content, __FILE__);
	return (1);
}
