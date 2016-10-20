/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_n_and_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 18:48:41 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/20 09:12:55 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	set_all_elem_old(t_list *head)
{
	while (head)
	{
		head->new = 0;
		head = head->next;
	}
}

void		flag_a(t_flags *flags)
{
	char		*tmp;
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if (termcaps->block_flag_a)
		return ;
	if (flags->argument)
	{
		tmp = ft_strdup(termcaps->path_historic_file);
		ft_strdel(&termcaps->path_historic_file);
		termcaps->path_historic_file = ft_strdup(flags->argument);
		save_historic_file(termcaps, 1);
		ft_strdel(&termcaps->path_historic_file);
		termcaps->path_historic_file = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else
		save_historic_file(termcaps, 1);
	set_all_elem_old(termcaps->head);
}

/*
** Même chose que le 'flag r' à la différence qu'ici seules les nouvelles
** (depuis la début de la sesions en cours) commandes sont prises en compte
*/

void		flag_n(t_flags *flags)
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
