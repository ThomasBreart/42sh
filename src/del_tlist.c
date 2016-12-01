/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_tlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 03:28:18 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/11 03:46:42 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	del_tlist(t_list *elem)
{
	ft_strdel(&elem->content);
	ft_strdel(&elem->fullcontent);
	free_double_tab(elem->argv);
	ft_memdel((void**)&elem);
}
