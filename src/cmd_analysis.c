/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_analysis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:08:05 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/04 16:47:55 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void		free_list(t_list *first)
{
	t_list	*elem;

	while (first != NULL)
	{
		elem = first;
		first = first->next;
		del_tlist(elem);
	}
}

/*
**		show_list(first);
**		show_elem(first);
**		show_binary_tree(root);
*/

t_list		*cmd_analysis(char **entry)
{
	t_list	*first;
	t_list	*root;

	first = NULL;
	root = NULL;
	if (check_event_designators(entry) == -1)
		return (NULL);
	if (lexical_analysis(*entry, &first) == -1 || first == NULL)
		return (NULL);
	if (formatting_cmd_general(&first) == 1)
	{
		check_backquotes(&first);
		root = semantic_analysis(first);
		if (root == NULL)
		{
			free_list(first);
			internal_error("cmd_analysis", "Root NULL", 0);
			return (NULL);
		}
	}
	return (root);
}
