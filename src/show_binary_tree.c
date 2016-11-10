/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 03:14:15 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/14 08:55:31 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void aff(t_list *racine, int prof)
{
	int i;
	for (i=0; i < prof; i++)
	{
		fputs("|___ ", stdout);
	}

	printf("[%s]\n", racine->content);
	if (racine->left != NULL) aff(racine->left, prof + 1);
	if (racine->right != NULL) aff(racine->right, prof + 1);
}

void	show_binary_tree(t_list *root)
{
	aff(root, 0);
		/* printf("[\"%s\"|Size:%zu|Type:%d]\n", root->content, root->content_size, root->type); */
}
