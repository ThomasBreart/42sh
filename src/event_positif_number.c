/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_positif_number.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:46:09 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/12 13:40:09 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		is_event_positif_number(char *str)
{
	++str;
	while (*str != '\0' && *str >= '0' && *str <= '9')
		++str;
	if (*str == '\0')
		return (1);
	return (0);
}

int		event_positif_number(char *sub_cmd, char **new_str)
{
	t_historic	*termcaps;
	int			cmd_number;
	int			i;
	t_list		*cmd_histo;

	termcaps = get_termcaps();
	cmd_number = ft_atoi(sub_cmd + 1);
	i = 1;
	cmd_histo = termcaps->head;
	while (i < cmd_number)
	{
		if (cmd_histo == termcaps->end)
			break ;
		cmd_histo = cmd_histo->next;
		++i;
	}
	if (i < cmd_number)
		return (E_NOT_FOUND);
	*new_str = s_strdup(cmd_histo->content, __FILE__);
	return (1);
}
