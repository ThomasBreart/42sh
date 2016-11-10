/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 10:59:15 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/10 17:37:41 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	modifie le maillon en fonction de son argv
*/

void	update_elem(t_list *elem, int change_argv)
{
	char	**tmp;

	ft_strdel(&elem->content);
	ft_strdel(&elem->fullcontent);
	elem->fullcontent = ft_implode(elem->argv);
	if (change_argv == 1)
	{
		tmp = s_strsplit_with_quote(elem->fullcontent, ' ', __FILE__);
		free_double_tab(elem->argv);
		elem->argv = tmp;
	}
	if (ft_strlen(elem->fullcontent) == 0)
		elem->content = s_strdup(elem->fullcontent, __FILE__);
	else
		elem->content = s_strdup(elem->argv[0], __FILE__);
//	fprintf(stderr, "econttent: %s\n", elem->content);
}
