/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_flag_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:47:26 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/17 19:53:22 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "stdio.h"

int		del_element_list(t_list *first)
{
	if (first->next != NULL)
	{
		if (first->prev != NULL)
		{
			first->prev->next = first->next;
			first->next->prev = first->prev;
		}
		else
			first->next->prev = NULL;
	}
	if (first->prev != NULL)
	{
		if (first->next != NULL)
		{
			first->next->prev = first->prev;
			first->prev->next = first->next;
		}
		else
			first->prev->next = NULL;
	}
	ft_memdel((void**)&first->content);
	free_double_tab(first->argv);
	ft_memdel((void**)&first);
	return (1);
}


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
  t_list      *tmp;
  t_historic  *termcaps;

  termcaps = get_termcaps();
  skip_flags(&ar);
  if (*ar)
  {
    tmp = termcaps->end->prev;
    if (termcaps->end == termcaps->head)
      termcaps->head = NULL;
    del_element_list(termcaps->end);
    termcaps->end = tmp;
    termcaps->cur = tmp;
  }
  while (*ar)
  {
    ft_putstr(*ar);
    ft_putchar(' ');
    ft_putchar('\n');
    ar++;
  }
}
