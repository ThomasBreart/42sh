/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_elem_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:25:11 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/07 09:23:41 by tbreart          ###   ########.fr       */
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
	free(first->content);
	free_double_tab(first->argv);
	free(first);
	return (1);
}
