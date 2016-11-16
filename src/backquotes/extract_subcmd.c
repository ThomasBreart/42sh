/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_subcmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 07:04:51 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/16 22:18:42 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	subcmd_find(char **str, int i, char **sub_cmd, int *start_subcmd)
{
	int		len_subcmd;
	char	*new_str;
	char	*tmp;

	*start_subcmd = i;
	tmp = goto_next_backquote((*str + i));
	len_subcmd = tmp - (*str + i) + 1;
	*sub_cmd = s_strsub(*str, i, len_subcmd, __FILE__);
	new_str = s_strnew(ft_strlen(*str) - len_subcmd, __FILE__);
	ft_strncat(new_str, *str, *start_subcmd);
	ft_strcat(new_str, *str + (*start_subcmd + len_subcmd));
	ft_strdel(str);
	*str = new_str;
	return (1);
}

int			extract_subcmd(char **str, int start_analysis, int *start_subcmd,
																char **sub_cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	*start_subcmd = -1;
	while ((*str)[i] != '\0' && i < start_analysis)
		++i;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\\')
			++i;
		else if ((*str)[i] == '\'')
		{
			tmp = goto_next_quote(*str + i);
			i = tmp - *str;
		}
		else if ((*str)[i] == '`')
			return (subcmd_find(str, i, sub_cmd, start_subcmd));
		if ((*str)[i] != '\0')
			++i;
	}
	return (0);
}
