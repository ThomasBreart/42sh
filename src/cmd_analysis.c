/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_analysis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:08:05 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/12 13:32:44 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	show_list(t_list *first)
{
	while (first != NULL)
	{
		printf("->%s\n", first->content);
		first = first->next;
	}
}

t_list		*cmd_analysis(char **entry)
{
	t_list *first;
	t_list	*root;

	first = NULL;
	if (check_event_designators(entry) == -1)
		return (NULL);
	if (lexical_analysis(*entry, &first) == -1 || first == NULL)
		return (NULL);
	//	show_list(first);
	if (formatting_cmd_general(&first) == 1)
	{
		//		show_elem(first);
		check_backquotes(&first);
		//		show_elem(first);
		if (ft_strlen(first->content) == 0)// cas "`` | pwd"
		{
			del_tlist(first);
			return (NULL);
		}
		root = semantic_analysis(first);
		//		show_binary_tree(root);
		if (root == NULL)
		{
			//	del_list ?
			internal_error("cmd_analysis", "Root NULL", 0);
			return (NULL);
		}
	}
	else
		return (NULL);
	return (root);
}
