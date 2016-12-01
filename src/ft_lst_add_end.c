/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 10:46:57 by tbreart           #+#    #+#             */
/*   Updated: 2015/10/14 17:16:48 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	ft_lst_add_end(t_list *previous, t_list *new)
{
	if (previous == NULL)
		return ;
	previous->next = new;
	new->prev = previous;
	new->next = NULL;
}
