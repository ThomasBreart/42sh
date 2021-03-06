/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_s_and_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:47:26 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/25 13:49:24 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	skip_flags(char ***ar)
{
	*ar += 1;
	while (**ar)
	{
		if (*(**ar) == '-')
		{
			if (*(**ar + 1) == '-')
			{
				*ar += 1;
				break ;
			}
			else
				*ar += 1;
		}
		else
			break ;
	}
}

static void	print_arguments(char **ar)
{
	while (*ar)
	{
		ft_putstr(*ar);
		ft_putchar('\n');
		ar++;
	}
}

/*
** Affiche les arguments passés au 'flag p' sur la sortie standard.
*/

void		flag_p(char **ar)
{
	t_list		*tmp;
	t_historic	*termcaps;

	termcaps = get_termcaps();
	skip_flags(&ar);
	if (*ar)
	{
		if (termcaps->end && termcaps->end->prev)
			tmp = termcaps->end->prev;
		else
			tmp = NULL;
		if (termcaps->end == termcaps->head)
			termcaps->head = NULL;
		del_elem_list(termcaps->end);
		termcaps->end = tmp;
		termcaps->cur = tmp;
	}
	print_arguments(ar);
}

/*
** Copie les paramètres passés au 'flag s' dans l'historique
** sans les afficher sur la sortie standard.
*/

void		flag_s(char *str)
{
	t_list		*tmp;
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if (*str)
	{
		if (termcaps->end && termcaps->end->prev)
			tmp = termcaps->end->prev;
		else
			tmp = NULL;
		if (termcaps->end == termcaps->head)
			termcaps->head = NULL;
		del_elem_list(termcaps->end);
		termcaps->end = tmp;
		termcaps->cur = tmp;
		add_historic(termcaps, &str, 1, 1);
	}
}
