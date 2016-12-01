/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_a_or_w.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 18:09:46 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/20 12:05:38 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	set_all_elem_old(t_list *head)
{
	while (head)
	{
		head->new = 0;
		head = head->next;
	}
}

static void	save(t_flags *flags, t_historic *termcaps)
{
	if (flags->flag_a)
		save_historic_file(termcaps, 1);
	else
		save_historic_file(termcaps, 0);
}

/*
** Ajoute le contenu de l'historique actuel dans le fichier '.42sh_history'.
** Petite particularité du 'flag -a' qui n'ajoute que les nouveaux éléments.
*/

void		flag_a_or_w(t_flags *flags)
{
	char		*tmp;
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if (flags->flag_a && termcaps->block_flag_a)
		return ;
	if (flags->argument)
	{
		tmp = ft_strdup(termcaps->path_historic_file);
		ft_strdel(&termcaps->path_historic_file);
		termcaps->path_historic_file = ft_strdup(flags->argument);
		save(flags, termcaps);
		ft_strdel(&termcaps->path_historic_file);
		termcaps->path_historic_file = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else if (flags->flag_a)
	{
		save_historic_file(termcaps, 1);
		set_all_elem_old(termcaps->head);
	}
	else
		save_historic_file(termcaps, 0);
}
