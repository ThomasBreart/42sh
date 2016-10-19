/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 18:48:41 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/19 15:50:11 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Même chose que le 'flag r' à la différence qu'ici seules les nouvelles
** (depuis la début de la sesions en cours) commandes sont prises en compte
*/

void	flag_n(t_flags *flags)
{
	char		*tmp;
	char		**taab;
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if (flags->argument)
	{
		tmp = ft_strdup(termcaps->path_historic_file);
		ft_strdel(&termcaps->path_historic_file);
		termcaps->path_historic_file = ft_strdup(flags->argument);
		if ((taab = recover_historic_file(termcaps, 0)) != NULL)
			create_historic_list(termcaps, taab);
		ft_strdel(&termcaps->path_historic_file);
		termcaps->path_historic_file = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else
	{
		if ((taab = recover_historic_file(termcaps, 0)) != NULL)
			create_historic_list(termcaps, taab);
	}
	termcaps->n_indice = ft_lst_size(termcaps->head);
}
