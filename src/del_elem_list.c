/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_elem_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:25:11 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/07 18:08:55 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static	void	free_all(t_list *first)
{
	ft_memdel((void**)&first->content);
	free_double_tab(first->argv);
	ft_memdel((void**)&first);
}

int				del_elem_list(t_list *first)
{
	if (first && first->next != NULL)
	{
		if (first->prev != NULL)
		{
			first->prev->next = first->next;
			first->next->prev = first->prev;
		}
		else
			first->next->prev = NULL;
	}
	if (first && first->prev != NULL)
	{
		if (first->next != NULL)
		{
			first->next->prev = first->prev;
			first->prev->next = first->next;
		}
		else
			first->prev->next = NULL;
	}
	if (first)
		free_all(first);
	return (1);
}
