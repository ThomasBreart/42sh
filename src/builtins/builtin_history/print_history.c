/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:41:24 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/20 10:52:15 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
** La commande "history" a un padding particulier. Cette fonction sert
** à ajouter le bon nombre d'espaces pour être fidèle à l'affichage de
** la vraie builtin.
*/

static void	print_spaces(int max, int indice)
{
	int	delta;

	max += 2;
	delta = get_len_of_int(indice);
	while (delta < max)
	{
		ft_putchar(' ');
		delta++;
	}
}

/*
** Si une commande et modifiée, on affiche un petit astérisque après
** l'indice.
*/

static void	print_wildcard(t_historic *termcaps, t_list *cpy)
{
	if (termcaps->need_wildcard)
	{
		if (cpy->content_modified)
			ft_putchar('*');
		else
			ft_putchar(' ');
	}
}

/*
** Si la commande "history" est appellée avec un paramètre,
** on affiche le(s) 'n' dernier(s) élément(s).
*/

static void	print_n_history(t_list *cpy, int max, int n, int lst_size)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	while (n > 1)
	{
		cpy = cpy->prev;
		n--;
		lst_size--;
	}
	while (cpy)
	{
		print_spaces(max, lst_size);
		ft_putnbr(lst_size);
		print_wildcard(termcaps, cpy);
		ft_putchar(' ');
		ft_putstr(cpy->content);
		ft_putstr("\n");
		cpy = cpy->next;
		lst_size++;
	}
}

/*
** Si la commande "history" est appellée sans paramètre,
** on affiche l'historique en entier.
*/

static void	print_full_history(t_list *cpy, int max, t_historic *termcaps)
{
	int	i;

	i = 1;
	while (cpy)
	{
		print_spaces(max, i);
		ft_putnbr(i);
		print_wildcard(termcaps, cpy);
		ft_putchar(' ');
		ft_putstr(cpy->content);
		ft_putstr("\n");
		cpy = cpy->next;
		i++;
	}
}

/*
** Si n != 0, on affiche les n dernières lignes de l'historique, sinon on
** affiche l'historique en entier.
*/

void		print_history(int n)
{
	int			max;
	int			lst_size;
	t_list		*cpy;
	t_historic	*termcaps;

	termcaps = get_termcaps();
	cpy = termcaps->head;
	lst_size = ft_lst_size(cpy);
	max = get_len_of_int(lst_size);
	if (!n || n > lst_size)
		print_full_history(cpy, max, termcaps);
	else
	{
		cpy = termcaps->end;
		print_n_history(cpy, max, n, lst_size);
	}
}
