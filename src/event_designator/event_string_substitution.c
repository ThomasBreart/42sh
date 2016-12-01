/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_string_substitution.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 17:31:44 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/16 22:22:59 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int				is_event_string_substitution(char *str)
{
	if (*str == '^')
		return (1);
	return (0);
}

static void		extract_data_substitution(char *sub_cmd, char **new_subcmd,
																char **replace)
{
	char	*tmp;
	char	*tmp2;
	int		len;

	tmp = goto_next_char(sub_cmd + 1, '^');
	len = tmp - (sub_cmd + 1);
	*new_subcmd = s_strndup(sub_cmd + 1, len, __FILE__);
	if (tmp[0] == '\0' || tmp[1] == '\0')
		*replace = s_strdup("", __FILE__);
	else
	{
		tmp2 = goto_next_char(tmp + 1, '^');
		len = tmp2 - (tmp + 1);
		*replace = s_strndup(tmp + 1, len, __FILE__);
	}
}

static char		*str_substitution(char *content, char *pos, char *new_subcmd,
																char *replace)
{
	char	*strbefore;
	char	*strafter;
	char	*tmp;
	char	*new_str;

	strbefore = s_strndup(content, (pos - content), __FILE__);
	strafter = s_strdup(pos + ft_strlen(new_subcmd), __FILE__);
	tmp = s_strjoin(strbefore, replace, __FILE__);
	new_str = s_strjoin(tmp, strafter, __FILE__);
	free(strbefore);
	free(strafter);
	free(tmp);
	return (new_str);
}

int				event_string_substitution(char *sub_cmd, char **new_str)
{
	t_historic	*termcaps;
	t_list		*tmplist;
	char		*new_subcmd;
	char		*replace;
	char		*pos;

	termcaps = get_termcaps();
	if (ft_strlen(sub_cmd) == 1)
		return (E_NO_PREVSUB);
	extract_data_substitution(sub_cmd, &new_subcmd, &replace);
	if (ft_strlen(new_subcmd) == 0)
		return (E_NO_PREVSUB);
	tmplist = termcaps->end->prev;
	if ((pos = ft_strstr(tmplist->content, new_subcmd)) != NULL)
		*new_str = str_substitution(tmplist->content, pos, new_subcmd, replace);
	free(new_subcmd);
	free(replace);
	if (pos == NULL)
		return (E_NOT_FOUND);
	return (1);
}
