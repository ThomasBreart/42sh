/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 15:35:44 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/18 02:02:31 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	show_list(t_list *first)
{
	while (first != NULL)
	{
		printf("->%s\n", first->content);
		first = first->next;
	}
}

/*
**	affiche les informations d'un maillon
*/

void	show_elem(t_list *elem)
{
	fprintf(stderr, "------ func show_elem -------\n");
	fprintf(stderr, "elem->content: %s\n", elem->content);
	fprintf(stderr, "elem->fulllcontent: %s\n", elem->fullcontent);
	ft_print_tab(elem->argv);
	fprintf(stderr, "elem->type: %d\n", elem->type);
	fprintf(stderr, "elem->aggr_fd: %d\n", elem->aggr_fd);
	fprintf(stderr, "elem->parent (pointeur): %p\n", elem->parent);
	fprintf(stderr, "elem->prev (pointeur): %p\n", elem->prev);
	fprintf(stderr, "elem->next (pointeur): %p\n", elem->next);
	fprintf(stderr, "elem->left (pointeur): %p\n", elem->left);
	fprintf(stderr, "elem->right (pointeur): %p\n", elem->right);
	fprintf(stderr, "-----------------------------\n");
}
