/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 10:59:15 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/06 10:37:39 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int		only_spaces(char *str)
{
	while (*str != '\0' && *str == ' ')
		++str;
	if (*str == '\0')
		return (1);
	return (0);
}

static char		**empty_tab(void)
{
	char	**tmp;

	tmp = s_memalloc(sizeof(char*) * 2, __FILE__);
	tmp[0] = s_strdup("", __FILE__);
	tmp[1] = NULL;
	return (tmp);
}

/*
**	modifie le maillon en fonction de son argv
*/

void			update_elem(t_list *elem, int change_argv)
{
	ft_strdel(&elem->content);
	ft_strdel(&elem->fullcontent);
	elem->fullcontent = ft_implode(elem->argv);
	if (change_argv == 1)
	{
		free_double_tab(elem->argv);
		if (only_spaces(elem->fullcontent))
			elem->argv = empty_tab();
		else
			elem->argv = s_strsplit_with_quote(elem->fullcontent, ' ');
	}
	if (ft_strlen(elem->fullcontent) == 0)
		elem->content = s_strdup(elem->fullcontent, __FILE__);
	else
		elem->content = s_strdup(elem->argv[0], __FILE__);
}
