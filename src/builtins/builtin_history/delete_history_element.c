/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_history_element.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 15:05:00 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/18 15:05:11 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	delete_first_and_last_element(t_historic *termcaps)
{
	termcaps->head = NULL;
	termcaps->cur = NULL;
	termcaps->end = NULL;
}

static void	delete_first_element(t_historic *termcaps, t_list *cpy)
{
	cpy->next->prev = NULL;
	termcaps->head = cpy->next;
}

static void	delete_last_element(t_historic *termcaps, t_list *cpy)
{
	cpy->prev->next = NULL;
	termcaps->end = cpy->prev;
	termcaps->cur = cpy->prev;
}

static void	delete_last_visible_element(t_list *cpy)
{
	cpy->prev->next = cpy->next;
	cpy->next->prev = cpy->prev;
}

void		check_what_element_to_delete(t_historic *termcaps,
		t_list *cpy)
{
	if (cpy == termcaps->head && cpy == termcaps->end)
		delete_first_and_last_element(termcaps);
	else if (cpy == termcaps->head)
		delete_first_element(termcaps, cpy);
	else if (cpy == termcaps->end->prev)
		delete_last_visible_element(cpy);
	else if (cpy == termcaps->end)
		delete_last_element(termcaps, cpy);
	else
	{
		cpy->prev->next = cpy->next;
		cpy->next->prev = cpy->prev;
	}
	ft_memdel((void**)&cpy->content);
	ft_memdel((void**)&cpy);
}
