/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 03:14:15 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/18 02:01:39 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	aff(t_list *racine, int prof)
{
	int i;

	i = 0;
	while (i++ < prof)
	{
		fputs("|___ ", stdout);
	}
	printf("[%s]\n", racine->content);
	if (racine->left != NULL)
		aff(racine->left, prof + 1);
	if (racine->right != NULL)
		aff(racine->right, prof + 1);
}

void	show_binary_tree(t_list *root)
{
	aff(root, 0);
}
