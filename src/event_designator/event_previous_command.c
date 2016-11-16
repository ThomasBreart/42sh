/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_previous_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:35:42 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/12 13:36:01 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		is_event_previous_command(char *str)
{
	++str;
	if (*str == '!')
		return (1);
	return (0);
}

int		event_previous_command(char **new_str)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if (termcaps->end == NULL || termcaps->end->prev == NULL ||
			termcaps->end->prev->content == NULL)
		return (E_NOT_FOUND);
	*new_str = s_strdup(termcaps->end->prev->content, __FILE__);
	return (1);
}
