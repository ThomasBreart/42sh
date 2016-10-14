/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_flag_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:47:26 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/13 18:05:14 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Il faut utiliser la fonction qui gère les quotes (simples et doubles)
** sur la ligne de commande.
*/


void flag_p(char *str)
{
  char **argv;

  argv = NULL;
  if (str)
    argv = ft_strsplit(str, ' ');
  else
    return ;
  while (*argv)
  {
    ft_putstr(*argv);
    ft_putchar(' ');
    ft_putchar('\n');
    argv++;
  }
}
