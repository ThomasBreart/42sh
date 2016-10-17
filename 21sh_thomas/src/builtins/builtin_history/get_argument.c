/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 16:16:26 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/17 16:12:59 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Fonctions qui servent à récupérer le ou les arguments situés après les fonctions.
** En fonction de l'option, soit on recupère toute la ligne d'argument ou bien
** seulement jusqu'au prochain espace.
*/

static int    parse_line_until_end(char *argv)
{
  int   index;

  index = 0;
  while (*argv)
  {
    index++;
    argv++;
  }
  return (index);
}

static int    parse_line_until_space(char *argv)
{
  int   index;

  index = 0;
  while (*argv && *argv != ' ')
  {
    index++;
    argv++;
  }
  return (index);
}

char  *get_argument(char *argv, int end)
{
  char  *ret;
  char  *cpy;
  int   index;

  if (!*argv)
    return (NULL);
  cpy = argv;
  if (end)
    index = parse_line_until_end(argv);
  else
    index = parse_line_until_space(argv);
  ret = ft_strnew(index + 1);
  if (index)
    ret = ft_strncpy(ret, cpy, index);
  return (ret);
}
