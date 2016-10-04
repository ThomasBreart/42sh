/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_analysis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:08:05 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/24 19:26:08 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	show_analyse_lex(first);
**	show_binary_tree_lr(*root);
*/

int		cmd_analysis(t_list **root, char **entry)
{
	t_list *first;

	first = NULL;
	if (lexical_analysis(*entry, &first) == -1)
		return (-1);
	if (first == NULL)
		return (internal_error("cmd_analysis", "first NULL", 0));
	if (formatting_cmd_general(&first) == 1)
	{
		*root = semantic_analysis(first);
		if (*root == NULL)
			return (internal_error("cmd_analysis", "Root NULL", 0));
	}
	else
		return (-1);
	return (1);
}
