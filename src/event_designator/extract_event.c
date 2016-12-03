/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_event.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 05:10:44 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/02 16:29:22 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	event_find(char **str, int i, char **sub_cmd, int *start_subcmd)
{
	char	*tmp;
	int		len_subcmd;
	char	*new_str;

	*start_subcmd = i;
	if ((*str)[i + 1] == '?')
	{
		tmp = goto_next_char((*str + i + 2), '?');
		if (*tmp == '\0')
			tmp = goto_next_char((*str + i + 2), ' ');
		else
			++tmp;
	}
	else
		tmp = goto_next_char((*str + i), ' ');
	len_subcmd = tmp - (*str + i);
	*sub_cmd = s_strsub(*str, i, len_subcmd, __FILE__);
	new_str = s_strnew(ft_strlen(*str) - len_subcmd, __FILE__);
	ft_strncat(new_str, *str, *start_subcmd);
	ft_strcat(new_str, *str + (*start_subcmd + len_subcmd));
	ft_strdel(str);
	*str = new_str;
	return (1);
}

static int	quick_sub_find(char **str, int i, char **sub_cmd, int *start_subcmd)
{
	char	*tmp;
	int		len_subcmd;
	char	*new_str;

	*start_subcmd = i;
	tmp = goto_next_char(*str + i + 1, '^');
	if (*tmp == '^')
	{
		tmp = goto_next_char(tmp + 1, '^');
		len_subcmd = tmp + 1 - (*str + i);
	}
	else
		len_subcmd = tmp - (*str + i);
	*sub_cmd = s_strsub(*str, i, len_subcmd, __FILE__);
	new_str = s_strnew(ft_strlen(*str) - len_subcmd, __FILE__);
	ft_strncat(new_str, *str, *start_subcmd);
	ft_strcat(new_str, *str + (*start_subcmd + len_subcmd));
	ft_strdel(str);
	*str = new_str;
	return (1);
}

/*
**	check si c est un event
*/

static int	is_an_event(char *s)
{
	if (*s == '!')
	{
		++s;
		if (*s != '\0' && *s != ' ' && *s != 9 && *s != '=')
			return (1);
	}
	return (0);
}

int			extract_event(char **str, int start_analysis, int *start_subcmd,
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
		if ((*str)[i] == '\\' && (*str)[i + 1] != '\0')
			++i;
		else if ((*str)[i] == '[')
			i += goto_close_bracket(&(*str)[i + 1]);
		else if ((*str)[i] == '\'' || (*str)[i] == '\"')
		{
			tmp = goto_next_quote(*str + i);
			i = tmp - *str;
		}
		else if (is_an_event(*str + i) == 1)
			return (event_find(str, i, sub_cmd, start_subcmd));
		else if ((*str)[i] == '^')
			return (quick_sub_find(str, i, sub_cmd, start_subcmd));
		++i;
	}
	return (0);
}
