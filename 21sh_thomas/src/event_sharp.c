/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_sharp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:41:52 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/20 16:44:33 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		is_event_sharp(char *str)
{
	++str;
	if (*str == '#')
		return (1);
	return (0);
}

int		event_sharp(char *sub_cmd, char *entry, int start_subcmd, char **new_str)
{
	char *tmp;

	if (start_subcmd == 0)
		return (-1);
	*new_str = s_strndup(entry, start_subcmd, __FILE__);
	if (sub_cmd[2] != '\0')
	{
		tmp = s_strjoin(*new_str, sub_cmd + 2, __FILE__);
		ft_strdel(new_str);
		*new_str = tmp;
	}
	return (1);
}
