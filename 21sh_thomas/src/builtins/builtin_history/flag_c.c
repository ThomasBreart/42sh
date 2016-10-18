/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 15:02:57 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/18 14:33:34 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Supprime tout l'historique
*/

void flag_c(void)
{
  t_historic  *termcaps;

  termcaps = get_termcaps();
  free_historic(termcaps);
	termcaps->head = NULL;
	termcaps->cur = NULL;
	termcaps->end = NULL;
}
