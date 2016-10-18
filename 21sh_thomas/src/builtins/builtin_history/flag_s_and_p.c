/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_s_and_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:47:26 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/18 14:23:07 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void skip_flags(char ***ar)
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

static void print_arguments(char **ar)
{
	while (*ar)
	{
		ft_putstr(*ar);
		ft_putchar(' ');
		ft_putchar('\n');
		ar++;
	}
}

/*
** Affiche les arguments passés au 'flag p' sur la sortie standard.
*/

void flag_p(char **ar)
{
  t_list      *tmp;
  t_historic  *termcaps;

  termcaps = get_termcaps();
  skip_flags(&ar);
  if (*ar)
  {
    tmp = termcaps->end->prev;
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

void flag_s(char *str)
{
  t_list      *tmp;
  t_historic  *termcaps;

  termcaps = get_termcaps();
  if (*str)
  {
    tmp = termcaps->end->prev;
    if (termcaps->end == termcaps->head)
      termcaps->head = NULL;
    del_elem_list(termcaps->end);
    termcaps->end = tmp;
    termcaps->cur = tmp;
    add_historic(termcaps, &str, 1);
  }
}
