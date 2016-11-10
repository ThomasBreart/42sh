/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_string_anywhere.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:20:48 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/20 16:34:06 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		is_event_string_anywhere(char *str)
{
	++str;
	if (*str == '?')
		return (1);
	return (0);
}

int		event_string_anywhere(char *sub_cmd, char **new_str)
{
	t_historic *termcaps;
	t_list	*tmp;
	int		len;
	char	*new_subcmd;

	termcaps = get_termcaps();
	len = ft_strlen(sub_cmd);
	if (sub_cmd[len - 1] == '?')
		new_subcmd = s_strsub(sub_cmd, 2, (len - 3), __FILE__);
	else
		new_subcmd = s_strdup(sub_cmd + 2, __FILE__);
	tmp = termcaps->end->prev;///
	while (tmp != NULL)
	{
		if (ft_strstr(tmp->content, new_subcmd) != NULL)
		{
			*new_str = s_strdup(tmp->content, __FILE__);
			break ;
		}
		tmp = tmp->prev;
	}
	free(new_subcmd);
	if (tmp == NULL)
		return (E_NOT_FOUND);
	return (1);
}
