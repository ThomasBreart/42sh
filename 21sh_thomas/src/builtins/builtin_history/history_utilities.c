/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 12:36:18 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/17 17:22:57 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "ft_21sh.h"
#include "stdio.h"

int  ft_lst_size(t_list *cpy)
{
  int   i;
  t_historic  *termcaps;

  termcaps = get_termcaps();
  i = 0;
  while (cpy)
  {
    if (cpy->content_modified)
      termcaps->need_wildcard = 1;
    cpy = cpy->next;
    i++;
  }
  return (i);
}

/*
** Fonction qui prends en paramètre la taille de la string à copier
** aisni que le pointer sur char de la string en question.
*/

int         get_value(char *cpy, int index)
{
  char  *value;

  value = ft_strnew(index + 1);
  if (index)
    ft_strncpy(value, cpy, index);
  index = ft_atoi(value);
  ft_memdel((void**)&value);
  return (index);
}

/*
** Ces deux fonctions servent uniquement à faire l'inverse d'un ft_strsplit.
** On convertit un "char **" en "char *".
** On skip volontairement le premier élément du tableau, qui sera le nom de la
** commande, (ici history), et qui ne nous intéresse pas pour parser les
** options et arguments.
*/

static int  get_size(char **argv)
{
  int   i;
  int    len;

  len = 0;
  i = 1;
  while (argv[i])
  {
    len += ft_strlen(argv[i]);
    i++;
  }
  len += --i;
  return (len);
}

char     *reverse_split(char **argv)
{
  char  *ret;
  int    len;
  int   i;

  i = 1;
  len = get_size(argv);
  ret = (char*)ft_memalloc(sizeof(char) * (len + 1));
  while (argv[i])
  {
    ft_strcat(ret, argv[i]);
    if (argv[i + 1])
      ft_strcat(ret, " ");
    i++;
  }
  return (ret);
}
