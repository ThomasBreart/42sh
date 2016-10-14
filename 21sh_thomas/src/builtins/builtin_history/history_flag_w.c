/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_flag_w.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 18:09:46 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/14 16:34:30 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "stdio.h"

void flag_w(t_flags *flags)
{
  char        *tmp;
  t_historic  *termcaps;

  termcaps = get_termcaps();
  if (flags->argument)
  {
    tmp = ft_strdup(termcaps->path_historic_file);
    ft_strdel(&termcaps->path_historic_file);
    termcaps->path_historic_file = ft_strdup(flags->argument);
    save_historic_file(termcaps);
    ft_strdel(&termcaps->path_historic_file);
    termcaps->path_historic_file = ft_strdup(tmp);
    ft_strdel(&tmp);
  }
  else
    save_historic_file(termcaps);
}

void flag_r(t_flags *flags)
{
  char        *tmp;
  char        **taab;
  t_historic  *termcaps;

  termcaps = get_termcaps();
  if (flags->argument)
  {
    tmp = ft_strdup(termcaps->path_historic_file);
    ft_strdel(&termcaps->path_historic_file);
    termcaps->path_historic_file = ft_strdup(flags->argument);
    if ((taab = recover_historic_file(termcaps)) != NULL)
      create_historic_list(termcaps, taab);
    ft_strdel(&termcaps->path_historic_file);
    termcaps->path_historic_file = ft_strdup(tmp);
    ft_strdel(&tmp);
  }
  else
  {
    if ((taab = recover_historic_file(termcaps)) != NULL)
      create_historic_list(termcaps, taab);
  }
}
