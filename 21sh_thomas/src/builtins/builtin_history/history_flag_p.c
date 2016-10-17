/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_flag_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:47:26 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/17 18:10:41 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "stdio.h"

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

void flag_p(char **ar)
{
  skip_flags(&ar);
  while (*ar)
  {
    ft_putstr(*ar);
    ft_putchar(' ');
    ft_putchar('\n');
    ar++;
  }
}
