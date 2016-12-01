/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 17:29:43 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/12 13:41:10 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		event_string(char *sub_cmd, char **new_str)
{
	t_historic	*termcaps;
	t_list		*tmp;
	int			len;

	termcaps = get_termcaps();
	len = ft_strlen(sub_cmd + 1);
	tmp = termcaps->end->prev;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, sub_cmd + 1, len) == 0)
		{
			*new_str = s_strdup(tmp->content, __FILE__);
			break ;
		}
		tmp = tmp->prev;
	}
	if (tmp == NULL)
		return (E_NOT_FOUND);
	return (1);
}
