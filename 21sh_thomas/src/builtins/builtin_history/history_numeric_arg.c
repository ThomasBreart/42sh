/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_numeric_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 15:39:58 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/10 17:18:21 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "ctype.h"

/*
** On récupère et renvoie la valeure numérique pour la commande "history [n]"
*/

static int get_numeric_value(char *argv)
{
  char    *cpy;
  int     index;

  index = 0;
  cpy = argv;
  while (isnumber(*argv)) // fonction system à modifier
  {
    index++;
    argv++;
  }
  if (check_errors(argv, index))
    return (0);
  return (get_value(cpy, index));
}

/*
** "history [n]" pour afficher les 'n' derniers résultats.
** Si il y a un argument, mais qu'il ne commence pas par un tiret "-",
** c'est que l'on ne cherche pas une option, mais une valeure numérique.
** Si l'argument n'est pas de type "int", c'est une erreur !
*/

int check_numeric_arg(char *argv)
{
  int   value;

  while (*argv)
  {
    if (!isnumber(*argv)) // fonction system à modifier
      return (numeric_argument_error(argv));
    else
    {
      if (!(value = get_numeric_value(argv)))
        return (1);
      print_historyy(value);
      break ;
    }
    argv++;
  }
  return (0);
}
