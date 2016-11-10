/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 09:27:30 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/08 16:51:02 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	free_tree(t_list *root)
{
	t_list *tmp;
	t_list *tobefree;

	tmp = root->left;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	while (tmp != NULL)
	{
		free(tmp->content);
		free_double_tab(tmp->argv);
		ft_memdel((void**)&tmp->fullcontent);
		tobefree = tmp;
		tmp = tmp->next;
		free(tobefree);
	}
	free(root->content);
	free(root);
}
