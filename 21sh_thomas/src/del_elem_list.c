/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_elem_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:25:11 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/17 18:50:30 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		del_elem_list(t_list *first)
{
	if (first->next != NULL)
	{
		if (first->prev != NULL)
		{
			first->prev->next = first->next;
			first->next->prev = first->prev;
		}
		else
			first->next->prev = NULL;
	}
	if (first->prev != NULL)
	{
		if (first->next != NULL)
		{
			first->next->prev = first->prev;
			first->prev->next = first->next;
		}
		else
			first->prev->next = NULL;
	}
	ft_memdel((void**)&first->content);
	free_double_tab(first->argv);
	ft_memdel((void**)&first);
	return (1);
}
