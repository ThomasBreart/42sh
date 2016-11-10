/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_r_or_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 18:48:41 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/20 12:15:31 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	import(t_flags *flags, t_historic *termcaps)
{
	char		**taab;

	if (flags->flag_r)
	{
		if ((taab = recover_historic_file(termcaps, -1)) != NULL)
			create_historic_list(termcaps, taab);
	}
	else
	{
		if ((taab = recover_historic_file(termcaps, 0)) != NULL)
			create_historic_list(termcaps, taab);
	}
}

/*
** Ajoute le contenu du fichier '.42sh_history' à l'historique actuel.
** Petite particularité du 'flag -n' qui n'ajoute que les éléments qui
** n'ont pas encore été lues depuis le fichier.
*/

void		flag_r_or_n(t_flags *flags)
{
	char		*tmp;
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if (flags->argument)
	{
		tmp = ft_strdup(termcaps->path_historic_file);
		ft_strdel(&termcaps->path_historic_file);
		termcaps->path_historic_file = ft_strdup(flags->argument);
		import(flags, termcaps);
		ft_strdel(&termcaps->path_historic_file);
		termcaps->path_historic_file = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else
		import(flags, termcaps);
	if (flags->flag_n)
		termcaps->n_indice = ft_lst_size(termcaps->head);
}
