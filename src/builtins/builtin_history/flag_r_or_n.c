/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_r_or_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 18:48:41 by mfamilar          #+#    #+#             */
/*   Updated: 2016/12/06 15:13:16 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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
		tmp = s_strdup(termcaps->path_historic_file, __FILE__);
		ft_strdel(&termcaps->path_historic_file);
		termcaps->path_historic_file = s_strdup(flags->argument, __FILE__);
		import(flags, termcaps);
		ft_strdel(&termcaps->path_historic_file);
		termcaps->path_historic_file = s_strdup(tmp, __FILE__);
		ft_strdel(&tmp);
	}
	else
		import(flags, termcaps);
	if (flags->flag_n)
		termcaps->n_indice = ft_lst_size(termcaps->head);
}
