/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 10:59:15 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/13 10:59:28 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	modifie le maillon en fonction de son argv
*/

void	update_elem(t_list *elem/*, char *save_word, char *sub_cmd*/)
{
	char	**tmp;

	ft_strdel(&elem->content);
	ft_strdel(&elem->fullcontent);
	elem->fullcontent = ft_implode(elem->argv);
	tmp = s_strsplit_with_quote(elem->fullcontent, ' ', __FILE__);
	free_double_tab(elem->argv);
	elem->argv = tmp;
	elem->content = s_strdup(elem->argv[0], __FILE__);
//	fprintf(stderr, "econttent: %s\n", elem->content);
}
