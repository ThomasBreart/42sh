/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 08:11:09 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/24 13:22:56 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static t_hash	*create_hash_elem(char *bin, char *fullpath_bin)
{
	t_hash	*current;

	current = (t_hash*)s_memalloc(sizeof(t_hash), __FILE__);
	current->next = NULL;
	current->name_bin = s_strdup(bin, __FILE__);
	current->fullpath_bin = s_strdup(fullpath_bin, __FILE__);
	return (current);
}

/*
**	ft_printf("add_bin_to_hashtable\n");
**	ft_printf("add_bin_to_hashtable\n");
**	ft_printf("termcaps->hashtable[index] == NULL\n");
**	ft_printf("add_bin - add_to_table_listed\n");
**	ft_printf("elem->bin: %s\n", elem->name_bin);
*/

int				add_bin_to_hashtable(char *bin, char *fullpath_bin)
{
	t_historic		*termcaps;
	int				index;
	t_hash			*current;
	t_hash			*elem;

	if (fullpath_bin == NULL)
		return (-1);
	termcaps = get_termcaps();
	index = hash_content(bin);
	if ((current = create_hash_elem(bin, fullpath_bin)) == NULL)
		return (-1);
	if (termcaps->hashtable[index] == NULL)
		termcaps->hashtable[index] = current;
	else
	{
		elem = termcaps->hashtable[index];
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = current;
	}
	return (1);
}
