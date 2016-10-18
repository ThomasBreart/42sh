/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 15:38:34 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/18 14:41:44 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Un cas particulier en fonction de si on supprime le premier ou dernier élément
** de la liste.
*/

int del_indice_history(t_flags flags)
{
  t_list      *cpy;
  t_historic  *termcaps;
  int         i;

  i = 0;
  termcaps = get_termcaps();
  cpy = termcaps->head;
  if ((ft_lst_size(cpy)) < flags.indice)
    return (out_of_range(flags.argument));
  while (i < flags.indice - 1 && cpy->next)
  {
    cpy = cpy->next;
    i++;
  }
  check_what_element_to_delete(termcaps, cpy);
  return (0);
}


int put_flag_d(t_flags *flags)
{
  flags->flag_d = 1;
  return (0);
}

/*
** Le flag 'd' prend une valeure numérique (un indice) en paramètre et supprime
** l'indice de l'historique en question.
*/

int flag_d(char *args, t_flags *flags)
{
  char  *cpy;
  int   index;

  index = 0;
  args++;
  while (*args == ' ')
    args++;
  if (!*args)
    return (history_usage());
  cpy = args;
  while (*args && *args != ' ')
  {
    if (!ft_isnumber(*args)) //fonction system à recoder
      return (out_of_range(args - index));
    index++;
    args++;
  }
  flags->indice = get_value(cpy, index);
  flags->argument = ft_itoa(flags->indice);
  return (0);
}
