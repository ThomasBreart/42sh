/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_flag_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 15:02:57 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/14 11:45:30 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	free_historic(t_historic *termcaps)
{
	t_list		*tmp;
	t_list		*tmp2;

	tmp = termcaps->head;
	while (tmp != NULL)
	{
		tmp2 = tmp;
		ft_strdel(&tmp->content);
		tmp = tmp->next;
		ft_memdel((void**)&tmp2);
	}
  termcaps->head = NULL;
  termcaps->cur = NULL;
  termcaps->end = NULL;

}

/*
** Supprime tout l'historique
*/

void flag_c(void)
{
  t_historic  *termcaps;

  termcaps = get_termcaps();
  free_historic(termcaps);
}
